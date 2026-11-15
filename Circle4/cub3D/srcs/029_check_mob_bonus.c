/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   042_check_mob_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ucho <ucho@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/09 04:49:49 by ucho              #+#    #+#             */
/*   Updated: 2026/07/09 04:49:49 by ucho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D_bonus.h>

#ifdef BONUS

static int	is_mob_defined(t_game *game, t_idx type)
{
	t_idx	i;

	i = 0;
	while (i < MOB_COUNT)
	{
		if (game->asset.mobs[i][type].vec.len)
			return (1);
		i++;
	}
	return (0);
}

int	is_mob_complete(t_game *game, t_idx type)
{
	t_idx	i;

	i = 0;
	while (i < MOB_COUNT)
	{
		if (!game->asset.mobs[i][type].vec.len)
			return (0);
		i++;
	}
	return (1);
}

int	check_mob(t_game *game)
{
	t_bool	has_mob_spec;
	int		mob;
	t_idx	i;

	has_mob_spec = FALSE;
	i = -1;
	while (++i < SLOT_COUNT)
	{
		if (is_mob_defined(game, i))
		{
			has_mob_spec = TRUE;
			if (!is_mob_complete(game, i))
				return (put_err("PARSE", "Mob definition is incomplete"));
		}
	}
	mob = count_tile(game, 'M');
	if (mob > 0 && !has_mob_spec)
		return (put_err("MAP", "Mob used in map, but undefined"));
	if (mob > MOB_MAX)
		return (put_err("MAP", "Too many Mops in map"));
	return (0);
}

#endif
