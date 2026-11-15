/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   045_count_heal_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ucho <ucho@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/09 04:49:56 by ucho              #+#    #+#             */
/*   Updated: 2026/07/09 04:49:57 by ucho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D_bonus.h>

#ifdef BONUS

int	set_item_hp(t_idx type)
{
	return ((ITEM_HP << (type / ITEM_HEAL_TIER))
		+ (type % ITEM_HEAL_TIER) * ITEM_HEAL_STEP);
}

int	get_health_budget(t_game *game, t_num *counts)
{
	double	threat;
	double	budget;
	double	max_budget;
	t_idx	i;

	threat = 0.0;
	i = 0;
	while (i < SLOT_COUNT)
	{
		if (counts[i])
			threat += (double)counts[i]
				* set_mob_ap(i);
		i++;
	}
	budget = threat * MOB_THREAT_BIAS;
	max_budget = HERO_HP + count_tile(game, 'M') * ITEM_HP;
	budget = fmin(budget, max_budget);
	return ((int)(budget + 0.5));
}

int	count_heal(t_game *game, t_num *counts)
{
	t_num	budget;
	int		min_heal;
	t_num	heal;
	t_idx	i;

	budget = get_health_budget(game, counts);
	min_heal = 0;
	i = 0;
	while (i < SLOT_COUNT)
	{
		if (game->asset.item_heal[i].vec.len)
		{
			heal = set_item_hp(i);
			if (heal <= budget && !min_heal)
				min_heal = heal;
			else if (heal <= budget)
				min_heal = min(min_heal, heal);
		}
		i++;
	}
	if (!min_heal)
		return (0);
	return (budget / min_heal);
}

#endif
