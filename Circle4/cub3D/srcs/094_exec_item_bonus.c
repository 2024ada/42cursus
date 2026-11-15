/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   092_exec_item_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ucho <ucho@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/09 04:52:02 by ucho              #+#    #+#             */
/*   Updated: 2026/07/09 04:52:03 by ucho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D_bonus.h>

#ifdef BONUS

static void	interact_item(t_game *game, t_item *item)
{
	if (item->kind == 0 && game->hud.hand.mode == 0)
	{
		item->is_active = 0;
		game->state.num_goal++;
		if (game->state.num_goal >= ITEM_GOAL_COUNT)
			game->state.hero_score += 100;
	}
	else if (item->kind == 1 && game->state.hero_hp < HERO_HP)
	{
		item->is_active = 0;
		game->state.hero_hp = min(game->state.hero_hp
				+ set_item_hp(item->type), HERO_HP);
	}
	else if (item->kind == 2)
	{
		item->is_active = 0;
		game->state.gear_charge[item->type] += ITEM_GEAR_CHARGE;
	}
}

void	exec_item(t_game *game)
{
	t_item	*item;
	double	x;
	double	y;
	t_idx	i;

	i = -1;
	while (++i < game->entity.items.len)
	{
		item = (t_item *)vec_at(&game->entity.items, i);
		if (item && item->is_active)
		{
			x = game->cam.pos.x - item->pos.x;
			y = game->cam.pos.y - item->pos.y;
			if (x * x + y * y <= ITEM_GET_RANGE * ITEM_GET_RANGE)
				interact_item(game, item);
		}
	}
}

#endif
