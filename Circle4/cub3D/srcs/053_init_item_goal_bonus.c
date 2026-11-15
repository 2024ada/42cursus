/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   060_init_item_goal_bonus.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ucho <ucho@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/09 04:50:39 by ucho              #+#    #+#             */
/*   Updated: 2026/07/09 04:50:40 by ucho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D_bonus.h>

#ifdef BONUS

static void	fill_item_goal(t_game *game, t_ixy *cand, int *count)
{
	t_pos	x;
	t_pos	y;

	*count = 0;
	y = -1;
	while (++y < game->scene.map.size.h)
	{
		x = -1;
		while (++x < game->scene.map.size.w)
		{
			if (is_empty_tile(game, (t_ixy){x, y}))
			{
				cand[*count] = (t_ixy){x, y};
				(*count)++;
			}
		}
	}
}

static int	pick_item_goal(t_game *game, t_ixy *cand, t_num count)
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

static void	push_item_goal(t_game *game, t_ixy tile)
{
	t_item	item;

	item.pos.x = tile.x + 0.5;
	item.pos.y = tile.y + 0.5;
	item.kind = 0;
	item.type = 0;
	item.is_active = 1;
	vec_push(&game->entity.items, &item);
}

void	init_item_goal(t_game *game)
{
	t_ixy	*cand;
	t_num	count;
	t_idx	pick;
	t_idx	i;

	cand = ft_xmalloc(sizeof(t_ixy) * game->scene.map.size.w
			* game->scene.map.size.h);
	fill_item_goal(game, cand, &count);
	i = -1;
	while (++i < ITEM_GOAL_COUNT && i < count)
	{
		pick = ft_rand() % count;
		if (i != 0)
			pick = pick_item_goal(game, cand, count);
		if (pick < 0)
			break ;
		push_item_goal(game, cand[pick]);
	}
	free(cand);
}

#endif
