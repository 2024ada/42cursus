/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   036_pixel_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ucho <ucho@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/09 04:49:33 by ucho              #+#    #+#             */
/*   Updated: 2026/07/09 04:49:34 by ucho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D_bonus.h>

#ifdef BONUS

int	get_tiled_pixel(t_img *img, t_dxy pos, double width, double height)
{
	double	u;
	double	v;
	t_ixy	tex;

	if (!img || !img->addr)
		return (0);
	if (img->size.w <= 0 || img->size.h <= 0)
		return (0);
	if (width <= 0.0 || height <= 0.0)
		return (0);
	u = pos.x / width;
	v = pos.y / height;
	u -= floor(u);
	v -= floor(v);
	tex.x = (int)(u * img->size.w);
	tex.y = (int)(v * img->size.h);
	tex.x = min(tex.x, img->size.w - 1);
	tex.y = min(tex.y, img->size.h - 1);
	return (get_pixel(img, tex));
}

int	has_transparent_pixel(t_img *tex, t_pos x)
{
	unsigned int	color;
	t_pos			y;

	y = tex->size.h - 1;
	while (y >= 0)
	{
		color = *(unsigned int *)(tex->addr
				+ y * tex->line_len + x * (tex->bpp / 8));
		if ((color & TRANSPARENT) != TRANSPARENT)
			break ;
		y--;
	}
	return (y < tex->size.h - 1);
}

int	is_transparent_pixel(t_img *tex, unsigned char *mask, t_idx i)
{
	unsigned int	color;
	t_pos			x;
	t_pos			y;

	if (i < 0 || i >= tex->size.w * tex->size.h || mask[i])
		return (0);
	x = i % tex->size.w;
	y = i / tex->size.w;
	color = *(unsigned int *)(tex->addr
			+ y * tex->line_len + x * (tex->bpp / 8));
	return ((color & TRANSPARENT) == TRANSPARENT);
}

#endif
