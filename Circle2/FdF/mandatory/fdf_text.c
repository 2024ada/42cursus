/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   function22.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ucho <ucho@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 15:11:17 by ucho              #+#    #+#             */
/*   Updated: 2025/08/19 11:52:53 by ucho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	put_glyph(t_fdf *fdf, char c, t_info *info)
{
	t_img			*img;
	char			**xpm;
	unsigned int	fg;
	unsigned int	bg;

	fg = str_to_hex((const char *)info->data);
	bg = get_pixel_color(&fdf->mlx.img, info->x, info->y);
	xpm = get_glyphs(fdf->glyphs[(int)c - 32], fg, bg);
	if (!xpm)
		return ;
	img = mlx_xpm_array_to_image(fdf->mlx.ctx, xpm);
	if (img && img->img)
	{
		put_xpm(&fdf->mlx.img,
			(t_info){info->x, info->y, img->width, img->height, img});
		info->x += img->width;
		mlx_destroy_image(fdf->mlx.ctx, img->img);
	}
	if (img)
		free(img);
	free_matrix(xpm, 0);
}

void	put_glyphs(t_fdf *fdf, char *str, t_info info)
{
	int	index;

	index = -1;
	while (str[++index])
	{
		if (0 <= (int)str[index] - 32 && (int)str[index] - 32 <= 94)
			put_glyph(fdf, str[index], &info);
	}
}
