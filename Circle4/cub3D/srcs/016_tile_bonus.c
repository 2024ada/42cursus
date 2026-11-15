/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   034_tile_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ucho <ucho@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/09 04:49:26 by ucho              #+#    #+#             */
/*   Updated: 2026/07/09 04:49:26 by ucho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D_bonus.h>

#ifdef BONUS

int	is_walkable_tile(t_game *game, t_ixy tile)
{
	char	symbol;

	if (tile.x < 0 || tile.y < 0)
		return (FALSE);
	if (tile.y >= game->scene.map.size.h
		|| game->scene.map.grid[tile.y] == NULL)
		return (FALSE);
	if (tile.x >= game->scene.map.size.w)
		return (FALSE);
	symbol = game->scene.map.grid[tile.y][tile.x];
	if (symbol == '1' || symbol == 'G')
		return (FALSE);
	if (is_door_sign(symbol))
	{
		if (game->scene.map.door[tile.y][tile.x].progress >= DOOR_PASS_RATIO)
			return (TRUE);
		if (!is_door_empty(game, tile.x, tile.y))
			return (TRUE);
		return (FALSE);
	}
	return (TRUE);
}

int	count_tile(t_game *game, char tile)
{
	t_pos	x;
	t_pos	y;
	t_num	count;

	count = 0;
	y = 0;
	while (y < game->scene.map.size.h)
	{
		x = 0;
		while (x < game->scene.map.size.w)
		{
			if (game->scene.map.grid[y][x] == tile)
				count++;
			x++;
		}
		y++;
	}
	return (count);
}

int	is_empty_tile(t_game *game, t_ixy tile)
{
	if (game->scene.map.grid[tile.y][tile.x] != '0'
		|| (game->cam.pos.x == tile.x && game->cam.pos.y == tile.y))
		return (0);
	if (has_prop(&game->entity.props, tile))
		return (0);
	if (has_mob(&game->entity.mobs, tile))
		return (0);
	if (has_item(&game->entity.items, tile))
		return (0);
	return (1);
}

#endif
