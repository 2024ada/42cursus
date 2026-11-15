/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   088_mouse_press_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ucho <ucho@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/09 04:51:53 by ucho              #+#    #+#             */
/*   Updated: 2026/07/09 04:51:53 by ucho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D_bonus.h>

#ifdef BONUS

static void	run_ending_button(t_app *app, t_game *game, t_idx mode)
{
	if (is_mouse_in_rect(app,
			(t_rect){{BUTTON_X + 1305, BUTTON_LEFT_Y}, {BUTTON_W, BUTTON_H}}))
	{
		if (mode == OUTRO_CLEAR)
		{
			app->core.curr_game = 0;
			game = &app->core.games[app->core.curr_game];
			game->snapshot.state.hero_hp = HERO_HP;
			game->snapshot.state.hero_score = 0;
		}
		load_snapshot(app, game);
		rend_app(app, game);
		return ;
	}
	if (is_mouse_in_rect(app,
			(t_rect){{BUTTON_X + 1305, BUTTON_RIGHT_Y}, {BUTTON_W, BUTTON_H}}))
		close_app(app);
}

static void	run_opening_button(t_app *app, t_game *game, t_idx mode)
{
	if (mode == INTRO_RULES && is_mouse_in_rect(app,
			(t_rect){{CLOSE_X, CLOSE_Y}, {CLOSE_W, CLOSE_H}}))
		app->screen.dissolve.mode = INTRO_TITLE;
	if (mode == INTRO_TITLE
		&& is_mouse_in_rect(app, (t_rect){{BUTTON_X, BUTTON_LEFT_Y},
			{BUTTON_W, BUTTON_H}}))
	{
		app->screen.dissolve.mode = FADEOUT_TITLE;
		app->screen.dissolve.started_at = game->state.now;
	}
	if (mode == INTRO_TITLE
		&& is_mouse_in_rect(app, (t_rect){{BUTTON_X, BUTTON_RIGHT_Y},
			{BUTTON_W, BUTTON_H}}))
		app->screen.dissolve.mode = INTRO_RULES;
	if (mode == INTRO_PROL
		&& is_mouse_in_rect(app, (t_rect){{NEXT_X, NEXT_Y}, {NEXT_W, NEXT_H}}))
	{
		if (app->screen.prologue < PROL_COUNT - 1)
			app->screen.prologue++;
		else
		{
			app->screen.dissolve.mode = FADEOUT_PROL;
			app->screen.dissolve.started_at = game->state.now;
		}
	}
}

int	mouse_press(int button, t_pos x, t_pos y, t_app *app)
{
	t_game	*game;
	t_idx	mode;

	game = &app->core.games[app->core.curr_game];
	get_mouse_pos(app, x, y);
	mode = app->screen.dissolve.mode;
	if (button == 1 && OUTRO_FAIL <= mode && mode <= OUTRO_CLEAR)
		return (run_ending_button(app, game, mode), 0);
	if (button == 1 && INTRO_TITLE <= mode && mode <= FADEOUT_PROL)
		return (run_opening_button(app, game, mode), 0);
	if (button == 1 && mode != GAME)
		return (0);
	if (button == 1 && game->state.hero_hp > 0)
	{
		app->input.mouse_drag = TRUE;
		app->input.last_mouse_x = x;
	}
	return (0);
}

#endif
