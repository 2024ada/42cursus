/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   011_draw_rect.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ucho <ucho@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/09 04:48:18 by ucho              #+#    #+#             */
/*   Updated: 2026/07/09 04:48:18 by ucho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

void	put_pixel(t_img *img, t_ixy pos, int color)
{
	char	*dst;

	if (!img || !img->addr)
		return ;
	if (pos.x < 0 || pos.x >= img->size.w
		|| pos.y < 0 || pos.y >= img->size.h)
		return ;
	dst = img->addr + (pos.y * img->line_len + pos.x * (img->bpp / 8));
	*(unsigned int *)dst = color;
}

void	draw_rect(t_app *app, t_rect rect, int color)
{
	t_ixy	pixel;

	pixel.y = rect.pos.y - 1;
	while (++pixel.y < rect.pos.y + rect.size.h)
	{
		pixel.x = rect.pos.x - 1;
		while (++pixel.x < rect.pos.x + rect.size.w)
			put_pixel(&app->core.screen, pixel, color);
	}
}
