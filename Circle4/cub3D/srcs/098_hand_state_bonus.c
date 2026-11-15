/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   095_hand_state_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ucho <ucho@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/09 04:52:07 by ucho              #+#    #+#             */
/*   Updated: 2026/07/09 04:52:08 by ucho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D_bonus.h>

#ifdef BONUS

void	face_mob_to_hero(t_game *game, t_mob *mob)
{
	t_dxy	delta;
	double	dist;

	delta.x = game->cam.pos.x - mob->pos.x;
	delta.y = game->cam.pos.y - mob->pos.y;
	dist = sqrt(delta.x * delta.x + delta.y * delta.y);
	if (dist < EPSILON)
		return ;
	mob->dir.x = delta.x / dist;
	mob->dir.y = delta.y / dist;
}

static void	set_hand_shot(t_game *game)
{
	int	start;
	int	next;

	if (game->hud.hand.mode == HAND_IDLE)
	{
		game->hud.hand.mode = HAND_SHOT;
		game->hud.hand.frame = 0;
		game->hud.hand.tick = 0;
	}
	else if (game->hud.hand.mode == HAND_SHOT)
	{
		next = (game->hud.hand.base_gear + 1) % SLOT_COUNT;
		start = next;
		while (!game->asset.hand_shot[next].vec.len)
		{
			next = (next + 1) % SLOT_COUNT;
			if (next == start)
				break ;
		}
		game->hud.hand.base_gear = next;
		game->hud.hand.frame = 0;
		game->hud.hand.tick = 0;
	}
}

static void	set_hand_idle(t_game *game)
{
	if (game->hud.hand.mode == HAND_SHOT)
	{
		game->hud.hand.mode = HAND_IDLE;
		game->hud.hand.frame = 0;
		game->hud.hand.tick = 0;
		game->hud.hand.is_shot = FALSE;
	}
}

static void	set_hand_fire(t_game *game)
{
	if (game->hud.hand.mode == HAND_SHOT)
	{
		if (game->state.gear_charge[game->hud.hand.base_gear] <= 0)
			return ;
		game->state.gear_charge[game->hud.hand.base_gear]--;
		game->hud.hand.is_shot = TRUE;
		game->hud.hand.frame = 0;
		game->hud.hand.tick = 0;
	}
}

void	switch_hand(t_game *game, int keycode)
{
	if (keycode == XKEY_X)
		set_hand_shot(game);
	else if (keycode == XKEY_Z)
		set_hand_idle(game);
	else if (keycode == XKEY_C)
		set_hand_fire(game);
}

#endif
