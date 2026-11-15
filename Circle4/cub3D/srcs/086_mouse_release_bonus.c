/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   089_mouse_release_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ucho <ucho@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/09 04:51:55 by ucho              #+#    #+#             */
/*   Updated: 2026/07/09 04:51:56 by ucho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D_bonus.h>

#ifdef BONUS

void	get_mouse_pos(t_app *app, t_pos x, t_pos y)
{
	app->input.mouse.x = x * REND_W / WIN_W;
	app->input.mouse.y = y * REND_H / WIN_H;
	app->input.mouse_inside = (x >= 0 && x < WIN_W && y >= 0 && y < WIN_H);
	if (!app->input.mouse_inside)
	{
		app->input.mouse.x = -1;
		app->input.mouse.y = -1;
	}
}

int	mouse_release(int button, t_pos x, t_pos y, t_app *app)
{
	get_mouse_pos(app, x, y);
	if (button == 1)
		app->input.mouse_drag = 0;
	return (0);
}

int	mouse_move(t_pos x, t_pos y, t_app *app)
{
	t_game	*game;
	int		dist;
	double	rot;

	game = &app->core.games[app->core.curr_game];
	get_mouse_pos(app, x, y);
	if (!app->input.mouse_drag || app->screen.dissolve.mode != GAME)
		return (0);
	dist = x - app->input.last_mouse_x;
	app->input.last_mouse_x = x;
	if (dist == 0)
		return (0);
	rot = fabs((double)dist) * MOUSE_SENS;
	if (dist > 0)
		rotate_left(game, rot);
	else
		rotate_right(game, rot);
	return (0);
}

#endif
