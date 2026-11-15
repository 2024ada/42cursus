/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   037_draw_img_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ucho <ucho@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/09 04:49:36 by ucho              #+#    #+#             */
/*   Updated: 2026/07/09 04:49:36 by ucho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D_bonus.h>

#ifdef BONUS

void	draw_scaled_img(t_img *dst, t_img *src, t_rect rect)
{
	int		color;
	t_ixy	pixel;

	if (!dst || !src || !src->img || rect.size.w <= 0 || rect.size.h <= 0)
		return ;
	pixel.y = -1;
	while (++pixel.y < rect.size.h)
	{
		pixel.x = -1;
		while (++pixel.x < rect.size.w)
		{
			color = get_scaled_pixel(src, pixel, rect.size.w, rect.size.h);
			if (!is_transparent_color(color))
				put_pixel(dst, (t_ixy){rect.pos.x + pixel.x,
					rect.pos.y + pixel.y}, color);
		}
	}
}

void	draw_clipped_img(t_img *dst, t_img *src, t_rect rect, t_rect clip)
{
	int		color;
	t_ixy	pixel;

	if (!dst || !src || !src->img || rect.size.w <= 0 || rect.size.h <= 0)
		return ;
	pixel.y = rect.pos.y - 1;
	while (++pixel.y < rect.pos.y + rect.size.h)
	{
		pixel.x = rect.pos.x - 1;
		while (++pixel.x < rect.pos.x + rect.size.w)
		{
			if (pixel.x >= clip.pos.x && pixel.y >= clip.pos.y
				&& pixel.x < clip.pos.x + clip.size.w
				&& pixel.y < clip.pos.y + clip.size.h)
			{
				color = get_scaled_pixel(src,
						(t_ixy){pixel.x - rect.pos.x,
						pixel.y - rect.pos.y},
						rect.size.w, rect.size.h);
				if (!is_transparent_color(color))
					put_pixel(dst, pixel, color);
			}
		}
	}
}

void	draw_overlay(t_app *app, t_img *tex)
{
	unsigned int	color;
	t_pos			x;
	t_pos			y;

	if (!tex || !tex->img)
		return ;
	y = -1;
	while (++y < REND_H)
	{
		x = -1;
		while (++x < REND_W)
		{
			color = get_scaled_pixel(tex, (t_ixy){x, y}, REND_W, REND_H);
			if (!is_transparent_color(color))
				put_pixel(&app->core.screen, (t_ixy){x, y}, color);
		}
	}
}

#endif
