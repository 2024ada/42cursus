/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   025_key_press.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ucho <ucho@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/09 04:49:01 by ucho              #+#    #+#             */
/*   Updated: 2026/07/09 04:49:02 by ucho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

int	get_key_idx(int keycode)
{
	if (keycode == XKEY_W)
		return (KEY_W);
	if (keycode == XKEY_S)
		return (KEY_S);
	if (keycode == XKEY_A)
		return (KEY_A);
	if (keycode == XKEY_D)
		return (KEY_D);
	if (keycode == XKEY_LEFT)
		return (KEY_LEFT);
	if (keycode == XKEY_RIGHT)
		return (KEY_RIGHT);
	if (keycode == XKEY_Q)
		return (KEY_Q);
	if (keycode == XKEY_E)
		return (KEY_E);
	if (keycode == XKEY_R)
		return (KEY_R);
	if (keycode == XKEY_F)
		return (KEY_F);
	if (keycode == XKEY_SPACE)
		return (KEY_SPACE);
	return (-1);
}

#ifndef BONUS

int	key_press(int keycode, t_app *app)
{
	t_idx	i;

	if (keycode == XKEY_ESC)
		close_app(app);
	i = get_key_idx(keycode);
	if (i >= 0)
		app->input.keys[i] = TRUE;
	return (0);
}

#endif
