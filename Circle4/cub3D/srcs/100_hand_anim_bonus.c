/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   097_hand_anim_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ucho <ucho@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/09 04:52:12 by ucho              #+#    #+#             */
/*   Updated: 2026/07/09 04:52:12 by ucho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D_bonus.h>

#ifdef BONUS

void	set_hand(t_game *game, t_vec *hand)
{
	if (game->hud.hand.mode == HAND_IDLE || game->hud.hand.is_shot)
	{
		if (++game->hud.hand.tick > FRAME_DELAY)
		{
			game->hud.hand.frame++;
			if (game->hud.hand.mode == HAND_IDLE)
				game->hud.hand.frame %= hand->len;
			game->hud.hand.tick = 0;
		}
	}
	if (game->hud.hand.mode == HAND_SHOT)
	{
		if (!game->hud.hand.is_shot)
			game->hud.hand.frame = 0;
		else if (game->hud.hand.frame >= hand->len)
		{
			game->hud.hand.is_shot = FALSE;
			game->hud.hand.frame = 0;
			run_hand_fire(game);
		}
	}
	while (!game->hud.hand.is_shot
		&& game->hud.hand.queue_head < game->hud.hand.queue_tail)
		switch_hand(game, game->hud.hand.queue
		[(game->hud.hand.queue_head++) % QUEUE_MAX]);
}

#endif
