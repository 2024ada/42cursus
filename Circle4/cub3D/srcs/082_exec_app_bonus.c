/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   085_exec_app_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ucho <ucho@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/09 04:51:42 by ucho              #+#    #+#             */
/*   Updated: 2026/07/09 04:51:42 by ucho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D_bonus.h>

#ifdef BONUS

static void	update_mode(t_app *app, t_game *game)
{
	double	elapsed;
	t_idx	mode;

	mode = app->screen.dissolve.mode;
	elapsed = game->state.now - app->screen.dissolve.started_at;
	if (mode == FADEOUT_TITLE && elapsed >= DISSOLVE)
	{
		app->screen.dissolve
			= (struct s_dissolve){FADEIN_PROL, game->state.now};
		app->screen.prologue = 0;
	}
	else if (mode == FADEIN_PROL && elapsed >= DISSOLVE)
		app->screen.dissolve.mode = INTRO_PROL;
	else if (mode == FADEOUT_PROL && elapsed >= DISSOLVE)
		app->screen.dissolve
			= (struct s_dissolve){FADEIN_GAME, game->state.now};
	else if (mode == FADEIN_GAME && elapsed >= DISSOLVE)
		app->screen.dissolve = (struct s_dissolve){GAME, 0.0};
	else if (mode == DISSOLVE_FAIL && elapsed >= DISSOLVE * 2.0)
		app->screen.dissolve.mode = OUTRO_FAIL;
	else if (mode == DISSOLVE_CLEAR && elapsed >= DISSOLVE * 2.0)
		app->screen.dissolve.mode = OUTRO_CLEAR;
}

static void	run_round(t_app *app, t_game *game)
{
	if (app->input.keys[KEY_E])
		increase_hfov(game);
	if (app->input.keys[KEY_Q])
		decrease_hfov(game);
	if (app->input.keys[KEY_R])
		increase_vfov(game);
	if (app->input.keys[KEY_F])
		decrease_vfov(game);
	exec_door(game);
	exec_hero(app, game);
	exec_item(game);
	exec_mobs(game);
	rend_app(app, game);
}

static void	run_next_round(t_app *app, t_game *game)
{
	t_game	*next;
	double	elapsed;

	elapsed = game->state.now - app->screen.dissolve.started_at;
	if (elapsed < DISSOLVE
		|| app->core.curr_game + 1 >= app->core.game_count)
	{
		rend_app(app, game);
		return ;
	}
	next = &app->core.games[app->core.curr_game + 1];
	if (next->state.round_loaded)
		load_snapshot(app, next);
	else
		init_runtime(app, next);
	inherit_stat(game, next);
	save_snapshot(next);
	app->core.curr_game++;
	app->screen.dissolve.mode = FADEIN_GAME;
	app->screen.dissolve.started_at = next->state.now;
	rend_app(app, next);
}

static int	loop_app(t_app *app)
{
	t_game	*game;
	t_idx	mode;

	game = &app->core.games[app->core.curr_game];
	game->state.now = get_now();
	update_mode(app, game);
	mode = app->screen.dissolve.mode;
	if ((INTRO_TITLE <= mode && mode <= FADEOUT_PROL)
		|| mode == FADEIN_GAME
		|| (DISSOLVE_FAIL <= mode && mode <= OUTRO_CLEAR))
		return (rend_app(app, game), 0);
	if (mode == GAME && game->state.hero_hp > 0)
		return (run_round(app, game), 0);
	if (mode == FADEOUT_GOAL)
		return (run_next_round(app, game), 0);
	return (rend_app(app, game), 0);
}

void	exec_app(t_app *app)
{
	mlx_hook(app->core.win, XEVENT_KEY_PRESS, XMASK_KEY_PRESS, key_press, app);
	mlx_hook(app->core.win, XEVENT_KEY_RELEASE, XMASK_KEY_RELEASE,
		key_release, app);
	mlx_hook(app->core.win, XEVENT_BUTTON_PRESS, XMASK_BUTTON_PRESS,
		mouse_press, app);
	mlx_hook(app->core.win, XEVENT_BUTTON_RELEASE, XMASK_BUTTON_RELEASE,
		mouse_release,
		app);
	mlx_hook(app->core.win, XEVENT_MOTION_NOTIFY, XMASK_POINTER_MOTION,
		mouse_move, app);
	mlx_hook(app->core.win, XEVENT_DESTROY_NOTIFY, XMASK_STRUCTURE_NOTIFY,
		close_app, app);
	mlx_loop_hook(app->core.mlx, loop_app, app);
	mlx_loop(app->core.mlx);
}

#endif
