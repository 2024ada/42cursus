/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   068_draw_floor_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ucho <ucho@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/09 04:50:57 by ucho              #+#    #+#             */
/*   Updated: 2026/07/09 04:50:57 by ucho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D_bonus.h>

#ifdef BONUS

static t_img	*get_floor_tile(t_game *game, double fx, double fy)
{
	t_img	*img;
	t_pos	mx;
	t_pos	my;
	t_idx	zone;

	mx = (int)fx;
	my = (int)fy;
	zone = -1;
	if (game->scene.map.zone && is_in_map(game, mx, my))
		zone = game->scene.map.zone[my][mx];
	img = get_vec_img(&game->asset.background[0].vec, zone);
	if (img)
		return (img);
	return (get_vec_img(&game->asset.background[0].vec, 0));
}

static void	draw_floor_tile(t_img *screen, t_game *game, t_pos y)
{
	t_dxy	step;
	t_dxy	pos;
	t_ixy	pixel;
	t_img	*tile;
	double	dist;

	while (++y < REND_H)
	{
		dist = (((double)REND_H / 2 * game->cam.v_fov) + game->cam.eye_level)
			/ (y - REND_H / 2);
		step.x = dist * (game->cam.plane.x + game->cam.plane.x) / REND_W;
		step.y = dist * (game->cam.plane.y + game->cam.plane.y) / REND_W;
		pos.x = game->cam.pos.x + dist * (game->cam.dir.x - game->cam.plane.x);
		pos.y = game->cam.pos.y + dist * (game->cam.dir.y - game->cam.plane.y);
		(void)(TRUE && (pixel.x = -1, pixel.y = y));
		while (++pixel.x < REND_W)
		{
			tile = get_floor_tile(game, pos.x, pos.y);
			if (tile)
				put_pixel(screen, pixel, get_tiled_pixel(tile, pos, 1.0, 1.0));
			else
				put_pixel(screen, pixel, game->asset.rgb[FLOOR]);
			(void)(TRUE && (pos.x += step.x, pos.y += step.y));
		}
	}
}

void	draw_floor(t_img *screen, t_game *game)
{
	t_pos	x;
	t_pos	y;

	if (game->asset.background[0].vec.len)
	{
		draw_floor_tile(screen, game, REND_H / 2);
		return ;
	}
	y = REND_H / 2;
	while (++y < REND_H)
	{
		x = -1;
		while (++x < REND_W)
			put_pixel(screen, (t_ixy){x, y}, game->asset.rgb[FLOOR]);
	}
}

#endif
