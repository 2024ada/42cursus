/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   076_draw_doorright_bonus.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ucho <ucho@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/09 04:51:15 by ucho              #+#    #+#             */
/*   Updated: 2026/07/09 04:51:16 by ucho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D_bonus.h>

#ifdef BONUS

static double	get_right_depth(t_ray_hit hit, t_dxy world)
{
	double	depth;

	if (hit.face->side == 0)
	{
		depth = world.x - (double)hit.face->map.x;
		if (hit.ray.step.x < 0)
			depth = 1.0 - depth;
	}
	else
	{
		depth = world.y - (double)hit.face->map.y;
		if (hit.ray.step.y < 0)
			depth = 1.0 - depth;
	}
	return (depth);
}

static double	get_right_dist(t_game *game, t_ray_hit hit, double side_x)
{
	double	plane_pos;

	if (hit.face->side == 0)
	{
		if (hit.ray.dir.y == 0.0)
			return (-1.0);
		plane_pos = (double)hit.face->map.y + side_x;
		return ((plane_pos - game->cam.pos.y) / hit.ray.dir.y);
	}
	if (hit.ray.dir.x == 0.0)
		return (-1.0);
	plane_pos = (double)hit.face->map.x + side_x;
	return ((plane_pos - game->cam.pos.x) / hit.ray.dir.x);
}

static int	fill_right_sample(t_game *game, t_ray_hit hit,
	int frame_y, t_sample *pt)
{
	t_img	*frame;
	t_dxy	world;
	double	depth;
	double	plane_num;
	t_idx	type;

	type = get_tile(game, hit.face->map.x, hit.face->map.y) - 'a';
	frame = &game->asset.door[DOOR_FRAME][type].img;
	world.x = game->cam.pos.x + pt->dist * hit.ray.dir.x;
	world.y = game->cam.pos.y + pt->dist * hit.ray.dir.y;
	depth = get_right_depth(hit, world);
	if (depth < 0.0 || depth >= 1.0)
		return (0);
	pt->z = 1.0 - ((double)frame_y / (double)frame->size.h);
	plane_num = game->cam.eye_level + (double)REND_H
		* game->cam.v_fov * (0.5 - pt->z);
	pt->local.x = depth;
	pt->local.y = (double)frame_y / (double)frame->size.h;
	pt->screen_y = (double)(int)(REND_H / 2.0 + plane_num / pt->dist);
	return (pt->screen_y >= -REND_H && pt->screen_y <= REND_H * 2);
}

int	set_right_sample(t_game *game, t_ray_hit hit,
	int frame_y, t_sample *pt)
{
	t_img			*frame;
	t_idx			jamb[3];
	t_idx			type;

	type = get_tile(game, hit.face->map.x, hit.face->map.y) - 'a';
	frame = &game->asset.door[DOOR_FRAME][type].img;
	if (!game->runtime.door_shape[type].jamb_left
		|| !game->runtime.door_shape[type].jamb_right)
		return (0);
	jamb[0] = game->runtime.door_shape[type].jamb_right[frame_y];
	jamb[1] = game->runtime.door_shape[type].jamb_left[frame_y];
	if (jamb[0] < 0 || jamb[1] < 0 || jamb[0] == jamb[1])
		return (0);
	if ((hit.face->side == 0 && hit.ray.dir.x < 0)
		|| (hit.face->side == 1 && hit.ray.dir.y > 0))
	{
		jamb[2] = jamb[0];
		jamb[0] = frame->size.w - 1 - jamb[1];
		jamb[1] = frame->size.w - 1 - jamb[2];
	}
	pt->dist = get_right_dist(game, hit,
			((double)jamb[0] + 0.5) / (double)frame->size.w);
	return (pt->dist > 0.0 && pt->dist >= hit.span[0] - EPSILON
		&& pt->dist <= hit.span[1] + EPSILON
		&& fill_right_sample(game, hit, frame_y, pt));
}

void	draw_right_pixel(t_app *app, t_game *game, t_ixy pos,
	t_sample pt)
{
	unsigned int	color;
	t_tex			*tex;
	t_pos			x;
	t_pos			y;
	t_idx			type;

	if (pt.dist <= 0.0
		|| pt.dist >= app->rend.depth[pos.y * REND_W + pos.x])
		return ;
	type = get_tile(game, app->rend.hit.face->map.x,
			app->rend.hit.face->map.y) - 'a';
	tex = &game->asset.door[DOOR_RIGHT][type];
	x = (int)(pt.local.x * (double)tex->img.size.w);
	y = (int)(pt.local.y * (double)tex->img.size.h);
	if (x < 0 || x >= tex->img.size.w || y < 0 || y >= tex->img.size.h)
		return ;
	color = *(unsigned int *)
		(tex->img.addr + y * tex->img.line_len + x * (tex->img.bpp / 8));
	if (is_transparent_color(color))
		return ;
	put_pixel(&app->core.screen, pos, color);
	app->rend.depth[pos.y * REND_W + pos.x] = pt.dist;
}

#endif
