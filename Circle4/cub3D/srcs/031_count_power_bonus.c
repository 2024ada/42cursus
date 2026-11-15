/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   044_count_power_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ucho <ucho@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/09 04:49:54 by ucho              #+#    #+#             */
/*   Updated: 2026/07/09 04:49:54 by ucho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D_bonus.h>

#ifdef BONUS

int	set_hero_ap(t_idx type)
{
	t_num	damage;

	damage = (HERO_AP >> (type / MOB_PAIN_TIER))
		- (type % MOB_PAIN_TIER) * HERO_ATTACK_STEP;
	damage = max(damage, 1);
	return (damage);
}

static int	get_attack_budget(t_num *counts)
{
	t_num	damage;
	t_num	total;
	t_idx	i;

	total = 0;
	i = 0;
	while (i < SLOT_COUNT)
	{
		if (counts[i] > 0)
		{
			damage = set_hero_ap(i);
			total += counts[i] * ((MOB_HP + damage - 1) / damage);
		}
		i++;
	}
	return (total);
}

int	count_gear(t_game *game, t_num *counts)
{
	t_bool	has_gear_spec;
	t_num	budget;
	t_idx	i;

	has_gear_spec = FALSE;
	i = 0;
	while (i < SLOT_COUNT)
	{
		if (game->asset.item_gear[i].vec.len)
			has_gear_spec = TRUE;
		i++;
	}
	if (!has_gear_spec)
		return (0);
	budget = get_attack_budget(counts);
	if (budget <= 0)
		return (0);
	return ((budget + ITEM_GEAR_CHARGE - 1) / ITEM_GEAR_CHARGE);
}

int	get_hero_ap(t_mob *mob, double dist, double dot)
{
	double	range;
	double	angle;
	double	accuracy;
	t_num	power;

	range = 1.0 - dist / HERO_SIGHT;
	range = fmax(range, 0.0);
	angle = (dot - HERO_ANGLE) / (1.0 - HERO_ANGLE);
	angle = fmin(fmax(angle, 0.0), 1.0);
	accuracy = 0.70 + range * 0.20 + angle * 0.10;
	power = (int)(HERO_AP * accuracy * mob->damage_resist + 0.5);
	power = max(power, 1);
	return (power);
}

#endif
