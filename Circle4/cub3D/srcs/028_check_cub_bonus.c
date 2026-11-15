/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   041_check_cub_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ucho <ucho@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/09 04:49:46 by ucho              #+#    #+#             */
/*   Updated: 2026/07/09 04:49:46 by ucho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D_bonus.h>

#ifdef BONUS

int	check_door(t_game *game)
{
	const char	**grid = (const char **)game->scene.map.grid;
	t_pos		x;
	t_pos		y;

	y = -1;
	while (++y < game->scene.map.size.h)
	{
		x = -1;
		while (++x < game->scene.map.size.w)
		{
			if (grid[y][x] >= 'a' && grid[y][x] <= 'z')
			{
				if (!game->asset.door[DOOR_FRAME][grid[y][x] - 'a'].path)
					return (put_err("MAP", "Door used in map, but undefined"));
				if ((x > 0 && x + 1 < game->scene.map.size.w
						&& grid[y][x - 1] == '1' && grid[y][x + 1] == '1') ==
					(y > 0 && y + 1 < game->scene.map.size.h
						&& grid[y - 1][x] == '1' && grid[y + 1][x] == '1'))
					return (put_err("MAP", "Door must be flanked by walls"));
			}
		}
	}
	return (0);
}

int	check_goal(t_game *game)
{
	char	**grid;
	t_num	count;
	t_pos	x;
	t_pos	y;

	grid = game->scene.map.grid;
	count = 0;
	y = -1;
	while (++y < game->scene.map.size.h)
	{
		x = -1;
		while (++x < game->scene.map.size.w)
			if (grid[y][x] == 'G' && ++count)
				if ((x > 0 && x + 1 < game->scene.map.size.w
						&& grid[y][x - 1] == '1' && grid[y][x + 1] == '1') ==
					(y > 0 && y + 1 < game->scene.map.size.h
						&& grid[y - 1][x] == '1' && grid[y + 1][x] == '1'))
					return (put_err("MAP", "Goal must be flanked by walls"));
	}
	if (count != 1)
		return (put_err("MAP", "Map must contain exactly one G tile"), 1);
	return (0);
}

int	check_prop(t_game *game)
{
	char	**grid;
	t_pos	x;
	t_pos	y;

	grid = game->scene.map.grid;
	y = 0;
	while (y < game->scene.map.size.h)
	{
		x = 0;
		while (x < game->scene.map.size.w)
		{
			if (ft_strchr(optional_ids(), grid[y][x])
				&& !game->asset.props[grid[y][x] - 'A'].path)
				return (put_err("MAP", "Prop used in map, but undefined"));
			x++;
		}
		y++;
	}
	return (0);
}

int	check_item(t_game *game)
{
	t_idx	i;

	i = 0;
	while (i < SLOT_COUNT)
	{
		if ((game->asset.item_gear[i].vec.len > 0)
			!= (game->asset.hand_shot[i].vec.len > 0))
			return (put_err("PARSE", "P_A and I_A definitions must match"));
		i++;
	}
	return (0);
}

#endif
