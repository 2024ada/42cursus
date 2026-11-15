/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   098_effect_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ucho <ucho@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/09 04:52:14 by ucho              #+#    #+#             */
/*   Updated: 2026/07/09 04:52:15 by ucho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D_bonus.h>

#ifdef BONUS

static void	switch_effect(t_game *game)
{
	if (game->state.hero_hp <= 0)
	{
		if (game->hud.effect.mode != DEATH)
		{
			game->hud.effect.mode = DEATH;
			game->hud.effect.frame = 0;
			game->hud.effect.tick = 0;
			game->hud.effect.is_done = FALSE;
		}
		else if (!game->hud.effect.is_done
			&& ++game->hud.effect.tick > FRAME_DELAY)
		{
			game->hud.effect.frame++;
			game->hud.effect.tick = 0;
		}
	}
	else if (game->state.now <= game->hud.effect.hurt_until)
		game->hud.effect.mode = PAIN;
	else
		game->hud.effect.mode = NONE;
}

void	set_effect(t_app *app, t_game *game, t_vec *effect)
{
	switch_effect(game);
	if (game->hud.effect.mode == PAIN)
		game->hud.effect.frame = 0;
	if (game->hud.effect.mode == DEATH)
	{
		if (game->hud.effect.is_done)
			game->hud.effect.frame = effect->len - 1;
		else if (game->hud.effect.frame + 1 >= effect->len)
		{
			game->hud.effect.is_done = TRUE;
			game->hud.effect.frame = effect->len - 1;
			app->screen.dissolve.mode = DISSOLVE_FAIL;
			app->screen.dissolve.started_at = game->state.now;
		}
	}
}

#endif
