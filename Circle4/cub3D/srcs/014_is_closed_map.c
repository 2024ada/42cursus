/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   008_is_closed_map.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ucho <ucho@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/09 04:48:07 by ucho              #+#    #+#             */
/*   Updated: 2026/07/09 04:48:07 by ucho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

static char	**pad_map(char **map, t_dim width, t_dim height)
{
	char	**padded_map;
	t_idx	i;

	padded_map = ft_xmalloc(sizeof(char *) * (height + 3));
	i = 0;
	while (i < height + 2)
	{
		padded_map[i] = ft_xmalloc(sizeof(char) * (width + 3));
		if (i == 0 || i == height + 1)
		{
			ft_memset(padded_map[i], ' ', width + 2);
			padded_map[i][width + 2] = '\0';
		}
		else
		{
			padded_map[i][0] = ' ';
			ft_memmove(padded_map[i] + 1, map[i - 1], width);
			padded_map[i][width + 1] = ' ';
			padded_map[i][width + 2] = '\0';
		}
		i++;
	}
	padded_map[i] = NULL;
	return (padded_map);
}

int	is_closed_map(t_game *game)
{
	char	**grid;
	t_pos	x;
	t_pos	y;

	grid = pad_map(game->scene.map.grid,
			game->scene.map.size.w, game->scene.map.size.h);
	y = -1;
	while (++y < game->scene.map.size.h + 2)
	{
		x = -1;
		while (++x < game->scene.map.size.w + 2)
		{
			if (is_walkable_sign(grid[y][x]))
			{
				if (y == 0 || y == game->scene.map.size.h + 1
					|| x == 0 || x == game->scene.map.size.w + 1)
					return (free_split(grid), 1);
				if (grid[y - 1][x] == ' ' || grid[y + 1][x] == ' '
					|| grid[y][x - 1] == ' ' || grid[y][x + 1] == ' ')
					return (free_split(grid), 1);
			}
		}
	}
	return (free_split(grid), 0);
}
