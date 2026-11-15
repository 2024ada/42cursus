/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   032_is_valid_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ucho <ucho@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/09 04:49:21 by ucho              #+#    #+#             */
/*   Updated: 2026/07/09 04:49:21 by ucho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D_bonus.h>

#ifdef BONUS

int	is_valid_sign(char tile)
{
	const char	symbols[] = " 01NSEWGM";

	return (ft_strchr(symbols, tile) || ft_strchr(optional_ids(), tile)
		|| is_door_sign(tile));
}

static int	is_valid_entry(t_tex_seq seq[SLOT_COUNT])
{
	t_idx	i;

	i = 0;
	while (i < SLOT_COUNT)
	{
		if (seq[i].vec.len > 0)
			return (TRUE);
		i++;
	}
	return (FALSE);
}

static int	is_valid_door(t_tex doors[DOOR_COUNT][SLOT_COUNT])
{
	t_bool	has_door;
	t_idx	i;
	t_idx	j;

	i = 0;
	has_door = FALSE;
	while (i < SLOT_COUNT)
	{
		if (doors[DOOR_FRAME][i].path)
		{
			has_door = TRUE;
			j = 0;
			while (j < DOOR_COUNT)
			{
				if (!doors[j][i].path)
					return (put_err("PARSE",
							"D[a-z] definition is incomplete"), FALSE);
				j++;
			}
		}
		i++;
	}
	if (!has_door)
		return (put_err("PARSE", "D[a-z] is unvalid"), FALSE);
	return (TRUE);
}

int	is_valid_premap(t_game *game)
{
	if (!game->asset.wall_base[WALL_NORTH].path
		|| !game->asset.wall_base[WALL_SOUTH].path
		|| !game->asset.wall_base[WALL_WEST].path
		|| !game->asset.wall_base[WALL_EAST].path)
		return (put_err("PARSE", "NO/SO/WE/EA are unvalid"), FALSE);
	if (game->asset.rgb[FLOOR] == -1
		|| game->asset.rgb[CEIL] == -1)
		return (put_err("PARSE", "F/C are unvalid"), FALSE);
	if (!is_valid_door(game->asset.door))
		return (FALSE);
	if (!game->asset.wall_goal.path)
		return (put_err("PARSE", "G is unvalid"), FALSE);
	if (!game->asset.item_goal.path)
		return (put_err("PARSE", "I_M is unvalid"), FALSE);
	if (!is_valid_entry(game->asset.item_gear))
		return (put_err("PARSE", "I_A[a-z] is unvalid"), FALSE);
	if (!game->asset.hand_idle.vec.len)
		return (put_err("PARSE", "P is unvalid"), FALSE);
	if (!is_valid_entry(game->asset.hand_shot))
		return (put_err("PARSE", "P_A[a-z] is unvalid"), FALSE);
	if (!game->asset.overlay_damage.vec.len)
		return (put_err("PARSE", "P_D is unvalid"), FALSE);
	if (game->asset.hud.vec.len != ITEM_GOAL_COUNT + 1)
		return (put_err("PARSE", "H is unvalid"), FALSE);
	return (TRUE);
}

#endif
