/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_image_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ucho <ucho@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 15:11:17 by ucho              #+#    #+#             */
/*   Updated: 2025/08/19 14:13:48 by ucho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

void	mlx_pixel_to_image(t_img *img, int x, int y, unsigned int color)
{
	char	*dst;

	if (x >= 0 && x < img->width && y >= 0 && y < img->height)
	{
		dst = img->addr + (y * img->line_len + x * (img->bpp / 8));
		*(unsigned int *)dst = color;
	}
}

void	*mlx_xpm_array_to_image(void *mlx, char **xpm)
{
	t_xpm			*map;
	t_img			*img;
	t_meta			meta;

	parse_meta(xpm, &meta);
	map = parse_palette(xpm + 1, meta.size, meta.cpp);
	if (!map)
		return (NULL);
	img = malloc(sizeof(t_img));
	if (!img)
	{
		free_palette(map);
		return (NULL);
	}
	img->width = meta.width;
	img->height = meta.height;
	img->img = mlx_new_image(mlx, img->width, img->height);
	img->addr = mlx_get_data_addr(img->img, &img->bpp,
			&img->line_len, &img->endian);
	put_xpm_pixels(img, map, &xpm[1 + meta.size], meta.cpp);
	free_palette(map);
	return (img);
}

void	put_panel(t_img *img, t_info info)
{
	int				x;
	int				y;
	unsigned int	color;

	color = str_to_hex((const char *)info.data);
	y = info.y;
	while (y < info.y + info.height)
	{
		x = info.x;
		while (x < info.x + info.width)
		{
			mlx_pixel_to_image(img, x, y, color);
			x++;
		}
		y++;
	}
}

void	put_xpm(t_img *dst, t_info info)
{
	t_img			src;
	int				x;
	int				y;
	int				offset;
	unsigned int	color;

	src = *(t_img *)info.data;
	y = -1;
	while (++y < info.height)
	{
		x = -1;
		while (++x < info.width)
		{
			offset = y * src.line_len + x * (src.bpp / 8);
			color = *(unsigned int *)(src.addr + offset);
			if (color == 0xFF000000)
				continue ;
			if (info.x + x >= 0 && info.x + x < WIN_W
				&& info.y + y >= 0 && info.y + y < WIN_H)
				mlx_pixel_to_image(dst, info.x + x, info.y + y, color);
		}
	}
}
