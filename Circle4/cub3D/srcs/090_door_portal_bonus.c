/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   091_door_portal_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ucho <ucho@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/09 04:52:01 by ucho              #+#    #+#             */
/*   Updated: 2026/07/09 04:52:01 by ucho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D_bonus.h>

#ifdef BONUS

static int	is_door_portal_row(t_img *frame, t_pos y, t_pos left, t_pos right)
{
	t_pos	x;

	if (left <= 0 || right >= frame->size.w - 1 || left > right)
		return (FALSE);
	x = -1;
	while (++x < left)
		if (is_transparent_color(get_pixel(frame, (t_ixy){x, y})))
			return (FALSE);
	x = left - 1;
	while (++x < right + 1)
		if (!is_transparent_color(get_pixel(frame, (t_ixy){x, y})))
			return (FALSE);
	x = right;
	while (++x < frame->size.w)
		if (is_transparent_color(get_pixel(frame, (t_ixy){x, y})))
			return (FALSE);
	return (TRUE);
}

static int	get_portal_range(t_game *game, t_idx type, double jamb[2])
{
	t_img	*frame;
	t_pos	y;

	frame = &game->asset.door[DOOR_FRAME][type].img;
	if (!frame->img
		|| !game->runtime.door_shape[type].jamb_left
		|| !game->runtime.door_shape[type].jamb_right)
		return (FALSE);
	y = frame->size.h;
	while (--y >= 0)
	{
		jamb[0] = game->runtime.door_shape[type].jamb_left[y];
		jamb[1] = game->runtime.door_shape[type].jamb_right[y];
		if (jamb[0] >= 0 && jamb[0] < frame->size.w
			&& jamb[1] >= jamb[0] && jamb[1] < frame->size.w
			&& is_door_portal_row(frame, y, (t_pos)(jamb[0]), (t_pos)(jamb[1])))
		{
			jamb[0] = jamb[0] / (double)frame->size.w;
			jamb[1] = (jamb[1] + 1.0) / (double)frame->size.w;
			return (jamb[0] < jamb[1]);
		}
	}
	return (FALSE);
}

int	get_jamb_box(t_game *game, t_ixy tile, t_box box[2])
{
	double	jamb[2];

	if (!box || !is_in_map(game, tile.x, tile.y)
		|| !is_door_sign(get_tile(game, tile.x, tile.y))
		|| game->scene.map.door[tile.y][tile.x].progress < DOOR_PASS_RATIO
		|| !get_portal_range(game, get_tile(game, tile.x, tile.y) - 'a',
			jamb))
		return (FALSE);
	if (is_wall_sign(get_tile(game, tile.x - 1, tile.y))
		&& is_wall_sign(get_tile(game, tile.x + 1, tile.y)))
	{
		box[0] = (t_box){{tile.x + jamb[0] / 2.0, tile.y + 0.5},
		{jamb[0] / 2.0, 0.5}};
		box[1] = (t_box){{tile.x + (jamb[1] + 1.0) / 2.0,
			tile.y + 0.5}, {(1.0 - jamb[1]) / 2.0, 0.5}};
		return (TRUE);
	}
	box[0] = (t_box){{tile.x + 0.5, tile.y + jamb[0] / 2.0},
	{0.5, jamb[0] / 2.0}};
	box[1] = (t_box){{tile.x + 0.5, tile.y + (jamb[1] + 1.0) / 2.0},
	{0.5, (1.0 - jamb[1]) / 2.0}};
	return (TRUE);
}

#endif
