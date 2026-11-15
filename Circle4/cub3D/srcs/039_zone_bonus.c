/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   039_zone_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ucho <ucho@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/09 04:49:41 by ucho              #+#    #+#             */
/*   Updated: 2026/07/09 04:49:42 by ucho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D_bonus.h>

#ifdef BONUS

static void	mark_zone(t_game *game, char **grid, t_pos x, t_pos y)
{
	if (!is_in_map(game, x, y))
		return ;
	if (!is_zone_sign(grid[y][x]))
		return ;
	grid[y][x] = 'z';
	game->scene.map.zone[y][x] = game->scene.map.zone_count;
	mark_zone(game, grid, x + 1, y);
	mark_zone(game, grid, x - 1, y);
	mark_zone(game, grid, x, y + 1);
	mark_zone(game, grid, x, y - 1);
}

char	**copy_map(t_game *game)
{
	char	**grid;
	t_pos	y;

	grid = (char **)ft_xmalloc(sizeof(char *) * (game->scene.map.size.h + 1));
	y = 0;
	while (y < game->scene.map.size.h)
	{
		grid[y] = ft_strdup(game->scene.map.grid[y]);
		y++;
	}
	grid[y] = NULL;
	return (grid);
}

void	set_zone_map(t_game *game)
{
	char	**grid;
	t_pos	x;
	t_pos	y;

	grid = copy_map(game);
	game->scene.map.zone = (int **)ft_xmalloc(sizeof(int *)
			* game->scene.map.size.h);
	y = -1;
	while (++y < game->scene.map.size.h)
	{
		game->scene.map.zone[y] = (int *)ft_xmalloc(sizeof(int)
				* game->scene.map.size.w);
		ft_memset(game->scene.map.zone[y], -1, sizeof(int)
			* game->scene.map.size.w);
	}
	x = -1;
	while (++x < game->scene.map.size.w)
	{
		y = -1;
		while (++y < game->scene.map.size.h)
			if (is_zone_sign(grid[y][x]))
				(mark_zone(game, grid, x, y), game->scene.map.zone_count++);
	}
	free_split(grid);
}

#endif
