/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   033_mouse_rect_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ucho <ucho@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/09 04:49:24 by ucho              #+#    #+#             */
/*   Updated: 2026/07/09 04:49:24 by ucho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D_bonus.h>

#ifdef BONUS

int	is_mouse_in_rect(t_app *app, t_rect rect)
{
	t_ixy	min;
	t_ixy	max;

	min.x = rect.pos.x;
	max.x = rect.pos.x + rect.size.w;
	min.y = rect.pos.y;
	max.y = rect.pos.y + rect.size.h;
	return (app->input.mouse_inside
		&& app->input.mouse.x >= min.x
		&& app->input.mouse.x <= max.x
		&& app->input.mouse.y >= min.y
		&& app->input.mouse.y <= max.y);
}

#endif
