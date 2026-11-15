/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   040_open_app_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ucho <ucho@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/09 04:49:44 by ucho              #+#    #+#             */
/*   Updated: 2026/07/09 05:05:26 by ucho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D_bonus.h>

#ifdef BONUS

static void	mark_reachable(t_map map, char **copy, t_pos x, t_pos y)
{
	if (x < 0 || y < 0)
		return ;
	if (x >= map.size.w || y >= map.size.h)
		return ;
	if (!is_walkable_sign(copy[y][x]))
		return ;
	copy[y][x] = '*';
	mark_reachable(map, copy, x + 1, y);
	mark_reachable(map, copy, x - 1, y);
	mark_reachable(map, copy, x, y + 1);
	mark_reachable(map, copy, x, y - 1);
}

static int	check_reachable(t_game *game)
{
	char	**grid;
	t_pos	x;
	t_pos	y;

	grid = copy_map(game);
	mark_reachable(game->scene.map, grid,
		game->scene.pos.x, game->scene.pos.y);
	y = 0;
	while (y < game->scene.map.size.h)
	{
		x = 0;
		while (x < game->scene.map.size.w)
		{
			if (is_walkable_sign(game->scene.map.grid[y][x])
				&& grid[y][x] != '*')
			{
				free_split(grid);
				return (put_err("MAP", "Map contains unreachable areas"));
			}
			x++;
		}
		y++;
	}
	return (free_split(grid), SUCCESS);
}

static int	check_available(t_game *game)
{
	t_num	available;
	t_num	required;
	t_num	counts[SLOT_COUNT];

	available = count_tile(game, '0');
	count_mob(game, counts);
	required = ITEM_GOAL_COUNT
		+ count_heal(game, counts) + count_gear(game, counts);
	if (available < required)
		return (put_err("MAP", "Not enough space to place items"));
	return (0);
}

static int	check_cub(t_game *game)
{
	if (is_closed_map(game))
		return (put_err("MAP", "Map is not closed by walls"));
	if (check_door(game) || check_goal(game))
		return (FAILURE);
	if (check_prop(game) || check_mob(game) || check_item(game))
		return (FAILURE);
	if (check_reachable(game) || check_available(game))
		return (FAILURE);
	set_zone_map(game);
	return (SUCCESS);
}

int	open_cub(char *path, t_game *game)
{
	char	*file;
	int		fd;
	size_t	len;

	game->asset.rgb[0] = -1;
	game->asset.rgb[1] = -1;
	init_cub(game);
	file = ft_strrchr(path, '/');
	if (file)
		file++;
	else
		file = path;
	len = ft_strlen(file);
	if (len < 4 || ft_strcmp(file + len - 4, ".cub"))
		return (put_err("INPUT", "The map extension must be '.cub'"));
	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (put_err("INPUT", "Cannot open map(.cub) file"));
	if (load_cub(game, fd) || check_cub(game))
		return (close(fd), FAILURE);
	return (close(fd), SUCCESS);
}

#endif
