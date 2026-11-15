/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   035_tile_occupancy_bonus.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ucho <ucho@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/09 04:49:28 by ucho              #+#    #+#             */
/*   Updated: 2026/07/09 04:49:29 by ucho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D_bonus.h>

#ifdef BONUS

int	has_prop(t_vec *props, t_ixy tile)
{
	t_prop	*prop;
	t_idx	i;

	i = -1;
	while (++i < props->len)
	{
		prop = (t_prop *)vec_at(props, i);
		if (prop && prop->pos.x == tile.x && prop->pos.y == tile.y)
			return (1);
	}
	return (0);
}

int	has_mob(t_vec *mobs, t_ixy tile)
{
	t_mob	*mob;
	t_idx	i;

	i = -1;
	while (++i < mobs->len)
	{
		mob = (t_mob *)vec_at(mobs, i);
		if (mob && mob->pos.x == tile.x && mob->pos.y == tile.y)
			return (1);
	}
	return (0);
}

int	has_item(t_vec *items, t_ixy tile)
{
	t_item	*item;
	t_idx	i;

	i = -1;
	while (++i < items->len)
	{
		item = (t_item *)vec_at(items, i);
		if (item && item->is_active
			&& item->pos.x == tile.x && item->pos.y == tile.y)
			return (1);
	}
	return (0);
}

double	rate_item_tile(t_game *game, t_vec *items, t_ixy tile)
{
	t_dxy	delta;
	double	dist;
	double	best;
	t_idx	i;

	delta = (t_dxy){(tile.x + 0.5) - game->cam.pos.x,
		(tile.y + 0.5) - game->cam.pos.y};
	best = delta.x * delta.x + delta.y * delta.y;
	i = -1;
	while (++i < items->len)
	{
		delta = (t_dxy){(tile.x + 0.5)
			- ((t_item *)vec_at(items, i))->pos.x,
			(tile.y + 0.5) - ((t_item *)vec_at(items, i))->pos.y};
		dist = delta.x * delta.x + delta.y * delta.y;
		best = fmin(best, dist);
	}
	return (best + (double)(ft_rand() % 1000) / 1000000.0);
}

#endif
