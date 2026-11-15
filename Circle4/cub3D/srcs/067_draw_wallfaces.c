/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   023_draw_wallfaces.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ucho <ucho@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/09 04:48:57 by ucho              #+#    #+#             */
/*   Updated: 2026/07/09 04:48:57 by ucho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

#ifndef BONUS

static void	put_wallface_pixel(t_app *app, t_face *face,
	t_ixy screen, int color)
{
	if (is_transparent_color(color))
		return ;
	if (face->side == 1)
		color = (color >> 1) & 0x7F7F7F;
	put_pixel(&app->core.screen, screen, color);
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
	tex_pos = (col->y[1] - col->pitch - REND_H / 2
			+ col->height / 2) * step;
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
	if (hit.face->side == 0 && hit.ray.step.x > 0)
		return (&game->asset.wall_base[WALL_EAST]);
	if (hit.face->side == 0)
		return (&game->asset.wall_base[WALL_WEST]);
	if (hit.ray.step.y > 0)
		return (&game->asset.wall_base[WALL_SOUTH]);
	return (&game->asset.wall_base[WALL_NORTH]);
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
	col.pitch = 0.0;
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
	col.clip[0] = 0;
	col.clip[1] = -1;
	draw_wallface_column(app, &tex->img, hit.face, &col);
}

#endif

void	draw_wallfaces(t_app *app, t_game *game, t_num count, t_pos x)
{
	t_face	tmp;
	int		best;
	t_idx	i;
	t_idx	j;

	i = -1;
	while (++i < count)
	{
		best = i;
		j = i;
		while (++j < count)
		{
			if (app->rend.hit.walls[j].dist
				> app->rend.hit.walls[best].dist)
				best = j;
		}
		if (best != i)
		{
			tmp = app->rend.hit.walls[i];
			app->rend.hit.walls[i] = app->rend.hit.walls[best];
			app->rend.hit.walls[best] = tmp;
		}
		app->rend.hit.face = &app->rend.hit.walls[i];
		draw_wallface(app, game, app->rend.hit, x);
	}
}
