/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   064_set_item_gear_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ucho <ucho@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/09 04:50:49 by ucho              #+#    #+#             */
/*   Updated: 2026/07/09 04:50:49 by ucho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D_bonus.h>

#ifdef BONUS

static int	pick_item_gear(t_game *game, t_ixy *cand, t_num count)
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

static void	push_item_gear(t_game *game, t_ixy tile, t_idx type)
{
	t_item	item;

	item.pos.x = tile.x + 0.5;
	item.pos.y = tile.y + 0.5;
	item.kind = 2;
	item.type = type;
	item.is_active = 1;
	vec_push(&game->entity.items, &item);
}

static void	fill_gear_type(t_game *game, t_idx *types, int *count)
{
	t_idx	i;

	*count = 0;
	i = -1;
	while (++i < SLOT_COUNT)
		if (game->asset.item_gear[i].vec.len > 0)
			types[(*count)++] = i;
}

void	set_item_gear(t_game *game, t_ixy *cand,
	t_num count, t_idx *types)
{
	t_num	counts[SLOT_COUNT];
	t_num	type_count;
	t_num	needed_items;
	t_idx	pick;
	t_idx	i;

	fill_gear_type(game, types, &type_count);
	count_mob(game, counts);
	needed_items = count_gear(game, counts);
	i = -1;
	while (type_count && ++i < needed_items)
	{
		pick = pick_item_gear(game, cand, count);
		if (pick < 0)
			break ;
		push_item_gear(game, cand[pick], types[i % type_count]);
	}
}

#endif
