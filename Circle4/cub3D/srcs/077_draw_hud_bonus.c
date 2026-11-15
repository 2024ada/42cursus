/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   081_draw_hud_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ucho <ucho@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/09 04:51:28 by ucho              #+#    #+#             */
/*   Updated: 2026/07/09 04:51:28 by ucho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D_bonus.h>

#ifdef BONUS

static void	draw_stats(t_app *app, t_game *game)
{
	t_tex	*tex;

	tex = (t_tex *)vec_at
		(&game->asset.item_gear[game->hud.hand.base_gear].vec, 0);
	draw_scaled_img(&app->core.screen, &tex->img,
		(t_rect){{HUD_GEAR_X, HUD_GEAR_Y},
	{HUD_GEAR_W, HUD_GEAR_H}});
	draw_number(app, app->core.curr_game + 1,
		(t_text){(t_ixy){HUD_ROUND_X, HUD_ROUND_Y},
		HUD_TEXT_SCALE, HUD_TEXT_COLOR, FONT_CENTER});
	draw_number(app, app->core.game_count,
		(t_text){(t_ixy){HUD_ROUND_X + 41, HUD_ROUND_Y},
		HUD_TEXT_SCALE, HUD_TEXT_COLOR, FONT_CENTER});
	draw_number(app, game->state.hero_hp,
		(t_text){(t_ixy){HUD_HP_X, HUD_HP_Y},
		HUD_TEXT_SCALE, HUD_TEXT_COLOR, FONT_CENTER});
	draw_number(app, game->state.hero_score,
		(t_text){(t_ixy){HUD_SCORE_X, HUD_SCORE_Y},
		HUD_TEXT_SCALE, HUD_TEXT_COLOR, FONT_CENTER});
	draw_number(app, game->state.num_goal,
		(t_text){(t_ixy){HUD_ITEM_X, HUD_ITEM_Y},
		HUD_ITEM_SCALE, HUD_ITEM_COLOR, FONT_CENTER});
	draw_number(app, game->state.gear_charge[game->hud.hand.base_gear],
		(t_text){(t_ixy){HUD_CHARGE_X, HUD_CHARGE_Y},
		HUD_CHARGE_SCALE, HUD_CHARGE_COLOR, FONT_CENTER});
}

void	draw_hud(t_app *app, t_game *game)
{
	t_tex	*tex;
	t_num	goal;

	goal = game->state.num_goal;
	goal = min(goal, game->asset.hud.vec.len - 1);
	tex = (t_tex *)vec_at(&game->asset.hud.vec, goal);
	draw_overlay(app, &tex->img);
	draw_stats(app, game);
}

#endif
