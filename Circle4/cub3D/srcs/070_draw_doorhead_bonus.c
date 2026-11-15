/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   074_draw_doorhead_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ucho <ucho@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/09 04:51:11 by ucho              #+#    #+#             */
/*   Updated: 2026/07/09 04:51:11 by ucho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D_bonus.h>

#ifdef BONUS

static double	get_doorhead_ratio(t_ray_hit hit, t_dxy local)
{
	if (hit.face->side == 0)
	{
		if (hit.ray.dir.x < 0)
			return (1.0 - local.y);
		return (local.y);
	}
	if (hit.ray.dir.y > 0)
		return (1.0 - local.x);
	return (local.x);
}

static double	get_doorhead_height(t_game *game, t_ray_hit hit, double ratio)
{
	t_door_shape	*shape;
	t_img			*frame;
	double			pos;
	t_idx			idx[2];
	t_idx			type;

	type = get_tile(game, hit.face->map.x, hit.face->map.y) - 'a';
	shape = &game->runtime.door_shape[type];
	frame = &game->asset.door[DOOR_FRAME][type].img;
	if (!shape->jamb_head || ratio < 0.0 || ratio >= 1.0)
		return (-1.0);
	pos = ratio * (double)frame->size.w;
	idx[0] = min(max((int)pos, 0), frame->size.w - 1);
	idx[1] = min(idx[0] + 1, frame->size.w - 1);
	if (shape->jamb_head[idx[0]] < 0.0 && shape->jamb_head[idx[1]] < 0.0)
		return (-1.0);
	if (shape->jamb_head[idx[0]] < 0.0)
		return (shape->jamb_head[idx[1]]);
	if (shape->jamb_head[idx[1]] < 0.0)
		return (shape->jamb_head[idx[0]]);
	return (shape->jamb_head[idx[0]]
		+ (shape->jamb_head[idx[1]] - shape->jamb_head[idx[0]])
		* (pos - (double)idx[0]));
}

int	set_doorhead_sample(t_game *game, t_ray_hit hit,
	double dist, t_sample *pt)
{
	t_dxy	world;
	double	ceil_z;
	double	ofs_y;

	if (dist <= 0.0)
		return (0);
	world.x = game->cam.pos.x + dist * hit.ray.dir.x;
	world.y = game->cam.pos.y + dist * hit.ray.dir.y;
	pt->local.x = world.x - (double)hit.face->map.x;
	pt->local.y = world.y - (double)hit.face->map.y;
	if (pt->local.x < 0.0 || pt->local.x >= 1.0
		|| pt->local.y < 0.0 || pt->local.y >= 1.0)
		return (0);
	ceil_z = get_doorhead_height(game, hit,
			get_doorhead_ratio(hit, pt->local));
	if (ceil_z < 0.0)
		return (0);
	ofs_y = game->cam.eye_level + (double)REND_H
		* game->cam.v_fov * (0.5 - ceil_z);
	pt->dist = dist;
	pt->z = ceil_z;
	pt->screen_y = (double)(int)(REND_H / 2.0 + ofs_y / dist);
	return (pt->screen_y >= -REND_H
		&& pt->screen_y <= REND_H * 2);
}

static void	draw_doorhead_pixel(t_app *app, t_game *game, t_ixy pos,
	t_sample pt)
{
	unsigned int	color;
	t_tex			*tex;
	t_idx			type;

	if (pt.dist >= app->rend.depth[pos.y * REND_W + pos.x])
		return ;
	type = get_tile(game, app->rend.hit.face->map.x,
			app->rend.hit.face->map.y) - 'a';
	tex = &game->asset.door[DOOR_HEAD][type];
	color = get_tiled_pixel(&tex->img, pt.local, 1.0, 1.0);
	if (is_transparent_color(color))
		return ;
	put_pixel(&app->core.screen, pos, color);
	app->rend.depth[pos.y * REND_W + pos.x] = pt.dist;
}

void	draw_doorhead_span(t_app *app, t_game *game,
	t_pos x, t_sample span[2])
{
	t_pos		y[2];
	double		ratio;
	t_sample	pt;

	if ((int)span[0].screen_y == (int)span[1].screen_y)
		return ;
	y[0] = (int)fmin(span[0].screen_y, span[1].screen_y);
	y[1] = (int)fmax(span[0].screen_y, span[1].screen_y);
	(void)(TRUE && (y[0] = max(y[0], 0) - 1, y[1] = min(y[1], REND_H - 1)));
	while (++y[0] <= y[1])
	{
		ratio = ((double)y[0] - span[0].screen_y)
			/ (span[1].screen_y - span[0].screen_y);
		if (ratio >= 0.0 && ratio <= 1.0)
		{
			pt.dist = span[0].dist + (span[1].dist - span[0].dist) * ratio;
			pt.local.x = span[0].local.x
				+ (span[1].local.x - span[0].local.x) * ratio;
			pt.local.y = span[0].local.y
				+ (span[1].local.y - span[0].local.y) * ratio;
			pt.z = span[0].z + (span[1].z - span[0].z) * ratio;
			pt.screen_y = (double)y[0];
			draw_doorhead_pixel(app, game, (t_ixy){x, y[0]}, pt);
		}
	}
}

#endif
