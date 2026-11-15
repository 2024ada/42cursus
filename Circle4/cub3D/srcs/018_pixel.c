/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   010_pixel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ucho <ucho@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/09 04:48:15 by ucho              #+#    #+#             */
/*   Updated: 2026/07/09 04:48:15 by ucho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

int	get_pixel(t_img *img, t_ixy pos)
{
	return (*(unsigned int *)(img->addr + pos.y * img->line_len
		+ pos.x * (img->bpp / 8)));
}

int	get_scaled_pixel(t_img *img, t_ixy pos, t_dim width, t_dim height)
{
	t_ixy	tex;

	tex.x = (pos.x * img->size.w) / width;
	tex.y = (pos.y * img->size.h) / height;
	return (get_pixel(img, tex));
}

int	is_transparent_color(int color)
{
	return ((color & TRANSPARENT) == TRANSPARENT);
}
