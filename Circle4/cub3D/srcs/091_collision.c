/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   028_collision.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ucho <ucho@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/09 04:49:09 by ucho              #+#    #+#             */
/*   Updated: 2026/07/09 04:49:09 by ucho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

int	is_box_overlap(t_box a, t_box b)
{
	return (a.center.x + a.half.x > b.center.x - b.half.x
		&& a.center.x - a.half.x < b.center.x + b.half.x
		&& a.center.y + a.half.y > b.center.y - b.half.y
		&& a.center.y - a.half.y < b.center.y + b.half.y);
}

#ifndef BONUS

int	overlap_wall(t_game *game, t_box actor)
{
	t_box	box;
	t_ixy	tile;

	tile.y = (int)floor(actor.center.y - actor.half.y) - 1;
	while (++tile.y <= (int)floor(actor.center.y + actor.half.y))
	{
		tile.x = (int)floor(actor.center.x - actor.half.x) - 1;
		while (++tile.x <= (int)floor(actor.center.x + actor.half.x))
		{
			if (!is_walkable_tile(game, tile))
			{
				box = (t_box){{tile.x + 0.5, tile.y + 0.5}, {0.5, 0.5}};
				if (is_box_overlap(actor, box))
					return (TRUE);
			}
		}
	}
	return (FALSE);
}

int	is_hero_blocked(t_game *game, double x, double y)
{
	t_box	player;

	player = (t_box){{x, y}, {HERO_MARGIN, HERO_MARGIN}};
	if (overlap_wall(game, player))
		return (TRUE);
	return (FALSE);
}

#endif
