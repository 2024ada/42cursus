/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   083_draw_scene_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ucho <ucho@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/09 04:51:32 by ucho              #+#    #+#             */
/*   Updated: 2026/07/09 04:51:32 by ucho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D_bonus.h>

#ifdef BONUS

static void	draw_opening(t_app *app)
{
	t_rect	screen;
	t_idx	mode;

	mode = app->screen.dissolve.mode;
	screen = (t_rect){(t_ixy){0, 0}, (t_iwh){REND_W, REND_H}};
	draw_dissolve(&app->core.screen, NULL, &app->assets.intro_title, 1.0);
	if (mode == INTRO_TITLE || mode == FADEOUT_TITLE)
		draw_button(app, FALSE);
	else if (mode == INTRO_RULES)
	{
		draw_scaled_img(&app->core.screen, &app->assets.button[0][ON], screen);
		draw_scaled_img(&app->core.screen, &app->assets.button[1][ON], screen);
		draw_scaled_img(&app->core.screen, &app->assets.intro_rules, screen);
	}
}

static void	draw_ending(t_app *app, t_game *game, t_img *img)
{
	t_rect	screen;
	double	alpha;

	screen = (t_rect){(t_ixy){0, 0}, (t_iwh){REND_W, REND_H}};
	alpha = (game->state.now - (app->screen.dissolve.started_at + DISSOLVE))
		/ DISSOLVE;
	alpha = fmin(fmax(alpha, 0.0), 1.0);
	draw_dissolve(&app->core.screen, NULL, img, alpha);
	if (alpha < 1.0)
		return ;
	if (img == &app->assets.outro_clear)
	{
		draw_scaled_img(&app->core.screen, &app->assets.outro_score, screen);
		draw_number(app, game->state.hero_score,
			(t_text){(t_ixy){FINAL_SCORE_X, FINAL_SCORE_Y},
			FINAL_SCORE_SCALE, FINAL_SCORE_COLOR, FONT_CENTER});
	}
	draw_button(app, TRUE);
}

void	draw_outro(t_app *app, t_game *game)
{
	double	alpha;
	t_idx	mode;
	t_img	*ending;

	mode = app->screen.dissolve.mode;
	if (mode < FADEIN_GAME)
		return ;
	if (FADEOUT_GOAL <= mode)
	{
		alpha = (game->state.now - app->screen.dissolve.started_at) / DISSOLVE;
		ending = NULL;
		if (mode == DISSOLVE_FAIL || mode == OUTRO_FAIL)
			ending = &app->assets.outro_fail;
		else if (mode == DISSOLVE_CLEAR || mode == OUTRO_CLEAR)
			ending = &app->assets.outro_clear;
	}
	if (mode == FADEIN_GAME)
		alpha = 1.0 - (game->state.now - app->screen.dissolve.started_at)
			/ DISSOLVE;
	alpha = fmin(fmax(alpha, 0.0), 1.0);
	if (mode == FADEIN_GAME || mode == FADEOUT_GOAL || alpha < 1.0)
		draw_dissolve(&app->core.screen, &app->core.screen, NULL, alpha);
	else if (DISSOLVE_FAIL <= mode)
		draw_ending(app, game, ending);
}

void	draw_intro(t_app *app, t_game *game)
{
	t_img	*prologue;
	double	alpha;
	t_idx	mode;

	mode = app->screen.dissolve.mode;
	if (mode < INTRO_TITLE || mode > FADEOUT_PROL)
		return ;
	alpha = fmin(fmax((game->state.now - app->screen.dissolve.started_at)
				/ DISSOLVE, 0.0), 1.0);
	prologue = &app->assets.prologue[app->screen.prologue];
	if (INTRO_TITLE <= mode && mode <= FADEOUT_TITLE)
	{
		draw_opening(app);
		if (mode == FADEOUT_TITLE)
			draw_dissolve(&app->core.screen, &app->core.screen, NULL, alpha);
	}
	else if (mode == FADEIN_PROL)
		draw_dissolve(&app->core.screen, NULL, prologue, alpha);
	else if (mode == INTRO_PROL)
		draw_dissolve(&app->core.screen, NULL, prologue, 1.0);
	else if (mode == FADEOUT_PROL)
	{
		draw_dissolve(&app->core.screen, NULL, prologue, 1.0);
		draw_dissolve(&app->core.screen, &app->core.screen, NULL, alpha);
	}
}

#endif
