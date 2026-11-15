/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   069_draw_dissolve_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ucho <ucho@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/09 04:50:59 by ucho              #+#    #+#             */
/*   Updated: 2026/07/09 04:50:59 by ucho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D_bonus.h>

#ifdef BONUS

int	blend_color(int from, int to, double alpha)
{
	int	r;
	int	g;
	int	b;

	r = (int)(((from >> 16) & 0xFF) * (1.0 - alpha)
			+ ((to >> 16) & 0xFF) * alpha);
	g = (int)(((from >> 8) & 0xFF) * (1.0 - alpha)
			+ ((to >> 8) & 0xFF) * alpha);
	b = (int)((from & 0xFF) * (1.0 - alpha)
			+ (to & 0xFF) * alpha);
	return ((r << 16) | (g << 8) | b);
}

void	draw_dissolve(t_img *dst, t_img *from, t_img *to, double alpha)
{
	t_ixy	pixel;
	int		color[2];

	if (!dst || !dst->img)
		return ;
	alpha = fmin(fmax(alpha, 0.0), 1.0);
	pixel.y = -1;
	while (++pixel.y < REND_H)
	{
		pixel.x = -1;
		while (++pixel.x < REND_W)
		{
			color[0] = 0;
			color[1] = 0;
			if (from && from->img)
				color[0] = get_scaled_pixel(from, pixel, REND_W, REND_H);
			if (to && to->img)
				color[1] = get_scaled_pixel(to, pixel, REND_W, REND_H);
			if (is_transparent_color(color[0]))
				color[0] = 0;
			if (is_transparent_color(color[1]))
				color[1] = 0;
			put_pixel(dst, pixel, blend_color(color[0], color[1], alpha));
		}
	}
}

#endif
