/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   024_exec_app.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ucho <ucho@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/09 04:48:59 by ucho              #+#    #+#             */
/*   Updated: 2026/07/09 04:49:00 by ucho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

int	close_app(t_app *app)
{
	destroy_app(app);
	return (exit(SUCCESS), SUCCESS);
}

int	key_release(int keycode, t_app *app)
{
	t_idx	i;

	i = get_key_idx(keycode);
	if (i >= 0)
		app->input.keys[i] = FALSE;
	return (0);
}

void	exec_hero(t_app *app, t_game *game)
{
	if (app->input.keys[KEY_W])
		move_forward(game, 0.05);
	if (app->input.keys[KEY_S])
		move_backward(game, 0.05);
	if (app->input.keys[KEY_A])
		strafe_left(game, 0.05);
	if (app->input.keys[KEY_D])
		strafe_right(game, 0.05);
	if (app->input.keys[KEY_LEFT])
		rotate_left(game, 0.03);
	if (app->input.keys[KEY_RIGHT])
		rotate_right(game, 0.03);
}

#ifndef BONUS

static int	loop_app(t_app *app)
{
	t_game	*game;

	game = &app->core.games[app->core.curr_game];
	exec_hero(app, game);
	return (rend_app(app, game), 0);
}

void	exec_app(t_app *app)
{
	mlx_hook(app->core.win, XEVENT_KEY_PRESS, XMASK_KEY_PRESS, key_press, app);
	mlx_hook(app->core.win, XEVENT_KEY_RELEASE, XMASK_KEY_RELEASE,
		key_release, app);
	mlx_hook(app->core.win, XEVENT_DESTROY_NOTIFY, XMASK_STRUCTURE_NOTIFY,
		close_app, app);
	mlx_loop_hook(app->core.mlx, loop_app, app);
	mlx_loop(app->core.mlx);
}

#endif
