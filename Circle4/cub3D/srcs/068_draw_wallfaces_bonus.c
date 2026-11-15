/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   072_draw_wallfaces_bonus.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ucho <ucho@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/09 04:51:06 by ucho              #+#    #+#             */
/*   Updated: 2026/07/09 04:51:06 by ucho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D_bonus.h>

#ifdef BONUS

static void	put_wallface_pixel(t_app *app, t_face *face,
	t_ixy screen, int color)
{
	if (is_transparent_color(color))
		return ;
	if (face->dist > app->rend.depth[screen.y * REND_W + screen.x] + 1e-6)
		return ;
	if (face->side == 1)
		color = (color >> 1) & 0x7F7F7F;
	put_pixel(&app->core.screen, screen, color);
	app->rend.depth[screen.y * REND_W + screen.x] = face->dist;
}

static void	draw_wallface_column(t_app *app, t_img *img,
	t_face *face, t_column *col)
{
	t_ixy	tex;
	double	step;
	double	tex_pos;
	t_pos	pos_y;

	tex.x = (int)(col->wall_x * (double)img->size.w);
	tex.x = min(max(tex.x, 0), img->size.w - 1);
	step = 1.0 * img->size.h / col->height;
	tex_pos = (col->y[1] - col->pitch - REND_H / 2 + col->height / 2) * step;
	pos_y = col->y[1] - 1;
	while (++pos_y <= col->y[2])
	{
		tex.y = (int)tex_pos + col->clip[0];
		tex_pos += step;
		if (col->clip[1] >= 0 && pos_y < col->clip[1])
			continue ;
		if (col->clip[0] > 0 && tex.y >= img->size.h)
			continue ;
		tex.y = min(max(tex.y, 0), img->size.h - 1);
		put_wallface_pixel(app, face,
			(t_ixy){col->x, pos_y}, get_pixel(img, tex));
	}
}

static t_tex	*get_wall_tile(t_game *game, t_ray_hit hit)
{
	char	tile;
	t_idx	i;

	tile = get_tile(game, hit.face->map.x, hit.face->map.y);
	if (is_door_sign(tile))
		return (&game->asset.door[DOOR_FRAME][tile - 'a']);
	if (tile == 'G' && game->state.num_goal >= ITEM_GOAL_COUNT)
		return (&game->asset.wall_goal);
	if (tile == '1' && game->scene.map.deco
		&& game->scene.map.deco[hit.face->map.y])
	{
		i = game->scene.map.deco[hit.face->map.y][hit.face->map.x];
		if (i >= 0 && i < (int)game->asset.wall_deco.vec.len)
			return ((t_tex *)vec_at(&game->asset.wall_deco.vec, i));
	}
	if (hit.face->side == 0 && hit.ray.step.x > 0)
		return (&game->asset.wall_base[WALL_EAST]);
	if (hit.face->side == 0)
		return (&game->asset.wall_base[WALL_WEST]);
	if (hit.ray.step.y > 0)
		return (&game->asset.wall_base[WALL_SOUTH]);
	return (&game->asset.wall_base[WALL_NORTH]);
}

static void	draw_doorpanel(t_app *app, t_game *game,
	t_ray_hit hit, t_column *col)
{
	t_img	*img;
	char	tile;
	t_idx	door;
	double	anim;

	if (!game->scene.map.door)
		return ;
	tile = get_tile(game, hit.face->map.x, hit.face->map.y);
	if (!is_door_sign(tile))
		return ;
	door = tile - 'a';
	img = &game->asset.door[DOOR_PANEL][door].img;
	anim = game->scene.map.door[hit.face->map.y][hit.face->map.x].progress;
	if (anim >= 1.0)
		return ;
	col->clip[0] = (int)(fmax(anim, 0.0) * (double)img->size.h);
	col->clip[1] = col->y[0]
		+ (int)(((double)game->runtime.door_shape[door].pivot
				/ (double)img->size.h) * (double)col->height);
	draw_wallface_column(app, img, hit.face, col);
}

void	draw_wallface(t_app *app, t_game *game, t_ray_hit hit, t_pos x)
{
	t_tex		*tex;
	t_column	col;

	tex = get_wall_tile(game, hit);
	if (hit.face->dist <= 0.0)
		return ;
	col.x = x;
	col.height = (int)((REND_H / hit.face->dist) * game->cam.v_fov);
	if (col.height <= 0)
		return ;
	col.pitch = game->cam.eye_level / hit.face->dist;
	col.y[0] = -col.height / 2 + REND_H / 2 + col.pitch;
	col.y[1] = max(col.y[0], 0);
	col.y[2] = col.height / 2 + REND_H / 2 + col.pitch;
	col.y[2] = min(col.y[2], REND_H - 1);
	col.wall_x = game->cam.pos.x + hit.face->dist * hit.ray.dir.x;
	if (hit.face->side == 0)
		col.wall_x = game->cam.pos.y + hit.face->dist * hit.ray.dir.y;
	col.wall_x -= floor(col.wall_x);
	if ((hit.face->side == 0 && hit.ray.dir.x < 0)
		|| (hit.face->side == 1 && hit.ray.dir.y > 0))
		col.wall_x = 1.0 - col.wall_x;
	draw_doorpanel(app, game, hit, &col);
	(void)(TRUE && (col.clip[0] = 0, col.clip[1] = -1));
	draw_wallface_column(app, &tex->img, hit.face, &col);
}

#endif
