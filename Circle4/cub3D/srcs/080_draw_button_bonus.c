/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   084_draw_button_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ucho <ucho@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/09 04:51:34 by ucho              #+#    #+#             */
/*   Updated: 2026/07/09 04:51:34 by ucho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D_bonus.h>

#ifdef BONUS

static void	set_button_hover(t_app *app, t_bool is_ending)
{
	t_ixy	win;
	t_rect	left;
	t_rect	right;

	app->screen.hover[LEFT] = 0;
	app->screen.hover[RIGHT] = 0;
	app->input.mouse_inside = 0;
	app->input.mouse.x = -1;
	app->input.mouse.y = -1;
	if (!mlx_mouse_get_pos(app->core.mlx, app->core.win, &win.x, &win.y))
		return ;
	if (win.x < 0 || win.x >= WIN_W || win.y < 0 || win.y >= WIN_H)
		return ;
	app->input.mouse_inside = 1;
	app->input.mouse.x = win.x * REND_W / WIN_W;
	app->input.mouse.y = win.y * REND_H / WIN_H;
	left = (t_rect){(t_ixy){BUTTON_X + is_ending * 1305, BUTTON_LEFT_Y},
		(t_iwh){BUTTON_W, BUTTON_H}};
	right = (t_rect){(t_ixy){BUTTON_X + is_ending * 1305,
		BUTTON_RIGHT_Y}, (t_iwh){BUTTON_W, BUTTON_H}};
	if (is_mouse_in_rect(app, left))
		app->screen.hover[LEFT] = TRUE;
	else if (is_mouse_in_rect(app, right))
		app->screen.hover[RIGHT] = TRUE;
}

void	draw_button(t_app *app, t_bool is_ending)
{
	t_img	*left;
	t_img	*right;
	t_rect	screen;

	set_button_hover(app, is_ending);
	if (app->screen.hover[LEFT])
		left = &app->assets.button[LEFT + is_ending * 2][OFF];
	else
		left = &app->assets.button[LEFT + is_ending * 2][ON];
	if (app->screen.hover[RIGHT])
		right = &app->assets.button[RIGHT + is_ending * 2][OFF];
	else
		right = &app->assets.button[RIGHT + is_ending * 2][ON];
	screen = (t_rect){(t_ixy){0, 0}, (t_iwh){REND_W, REND_H}};
	draw_scaled_img(&app->core.screen, left, screen);
	draw_scaled_img(&app->core.screen, right, screen);
}

#endif
