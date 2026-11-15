/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   043_count_mob_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ucho <ucho@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/09 04:49:51 by ucho              #+#    #+#             */
/*   Updated: 2026/07/09 04:49:52 by ucho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D_bonus.h>

#ifdef BONUS

static int	get_mob_weight(t_idx type)
{
	t_num	weight;

	weight = WEIGHT >> type;
	if (weight == 0)
		weight = 1;
	return (weight);
}

static int	set_mob_weights(t_game *game, int *weights)
{
	t_num	weight;
	t_idx	i;

	weight = 0;
	i = 0;
	while (i < SLOT_COUNT)
	{
		weights[i] = 0;
		if (is_mob_complete(game, i))
		{
			weights[i] = get_mob_weight(i);
			weight += weights[i];
		}
		i++;
	}
	return (weight);
}

static int	set_default_mobs(t_game *game, int *weights, t_num *counts)
{
	t_num	mob_tile;
	t_num	count;
	t_idx	i;

	mob_tile = count_tile(game, 'M');
	i = 0;
	count = 0;
	while (i < SLOT_COUNT)
	{
		counts[i] = 0;
		if (weights[i] && count < mob_tile)
		{
			counts[i] = 1;
			count++;
		}
		i++;
	}
	return (mob_tile - count);
}

int	set_mob_ap(t_idx type)
{
	return ((MOB_AP << (type / MOB_ATTACK_TIER))
		+ (type % MOB_ATTACK_TIER) * MOB_ATTACK_STEP);
}

void	count_mob(t_game *game, t_num *counts)
{
	t_num	weights[SLOT_COUNT];
	t_num	weight;
	t_num	mob_tile;
	t_num	count;
	t_idx	i;

	weight = set_mob_weights(game, weights);
	mob_tile = set_default_mobs(game, weights, counts);
	if (!weight || !mob_tile)
		return ;
	count = 0;
	i = -1;
	while (++i < SLOT_COUNT)
	{
		if (weights[i])
		{
			counts[i] += (weights[i] * mob_tile) / weight;
			count += (weights[i] * mob_tile) / weight;
		}
	}
	i = -1;
	while (++i < SLOT_COUNT && count < mob_tile)
		(void)((weights[i]) && (++counts[i], ++count));
}

#endif
