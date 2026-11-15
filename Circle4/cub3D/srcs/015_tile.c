/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   009_tile.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ucho <ucho@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/09 04:48:09 by ucho              #+#    #+#             */
/*   Updated: 2026/07/09 04:48:10 by ucho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

int	is_in_map(t_game *game, t_pos x, t_pos y)
{
	return (x >= 0 && y >= 0
		&& x < game->scene.map.size.w && y < game->scene.map.size.h);
}

char	get_tile(t_game *game, t_pos x, t_pos y)
{
	if (!is_in_map(game, x, y))
		return (' ');
	return (game->scene.map.grid[y][x]);
}

#ifndef BONUS

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
	if (symbol == '1')
		return (FALSE);
	return (TRUE);
}

#endif
