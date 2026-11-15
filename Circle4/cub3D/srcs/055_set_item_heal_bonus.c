/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   062_set_item_heal_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ucho <ucho@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/09 04:50:44 by ucho              #+#    #+#             */
/*   Updated: 2026/07/09 04:50:44 by ucho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D_bonus.h>

#ifdef BONUS

static int	pick_heal_type(t_idx *types, t_num count, t_num budget)
{
	t_num	weight;
	t_num	heal;
	t_idx	pick;
	t_idx	i;

	weight = 0;
	i = -1;
	while (++i < count)
		if (set_item_hp(types[i]) <= budget)
			weight += count - i;
	if (weight <= 0)
		return (-1);
	pick = ft_rand() % weight;
	i = -1;
	while (++i < count)
	{
		heal = set_item_hp(types[i]);
		if (heal <= budget && pick < count - i)
			return (types[i]);
		if (heal <= budget)
			pick -= count - i;
	}
	return (-1);
}

static int	pick_heal_tile(t_game *game, t_ixy *cand, t_num count)
{
	double	best_score;
	double	score;
	t_idx	best;
	t_idx	i;

	best_score = -1.0;
	best = -1;
	i = -1;
	while (++i < count)
	{
		if (is_empty_tile(game, cand[i]))
		{
			score = rate_item_tile(game, &game->entity.items, cand[i]);
			if (score > best_score)
			{
				best_score = score;
				best = i;
			}
		}
	}
	return (best);
}

static void	push_item_heal(t_game *game, t_ixy tile, t_idx type)
{
	t_item	item;

	item.pos.x = tile.x + 0.5;
	item.pos.y = tile.y + 0.5;
	item.kind = 1;
	item.type = type;
	item.is_active = 1;
	vec_push(&game->entity.items, &item);
}

static void	fill_heal_type(t_game *game, t_idx *types, int *count)
{
	t_idx	i;

	*count = 0;
	i = -1;
	while (++i < SLOT_COUNT)
		if (game->asset.item_heal[i].vec.len > 0)
			types[(*count)++] = i;
}

void	set_item_heal(t_game *game, t_ixy *cand,
	t_num count, t_idx *types)
{
	t_num	counts[SLOT_COUNT];
	t_num	budget;
	t_num	type_count;
	t_idx	type;
	t_idx	pick;

	fill_heal_type(game, types, &type_count);
	count_mob(game, counts);
	budget = get_health_budget(game, counts);
	while (type_count && budget >= ITEM_HP)
	{
		type = pick_heal_type(types, type_count, budget);
		pick = pick_heal_tile(game, cand, count);
		if (type < 0 || pick < 0)
			break ;
		push_item_heal(game, cand[pick], type);
		budget -= set_item_hp(type);
	}
}

#endif
