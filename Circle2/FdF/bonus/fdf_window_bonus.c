/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_window_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ucho <ucho@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 15:11:17 by ucho              #+#    #+#             */
/*   Updated: 2025/08/19 14:15:07 by ucho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

void	put_top(t_fdf *fdf)
{
	t_img	img;
	t_img	*xpm;
	char	*count;

	img = fdf->mlx.img;
	xpm = fdf->widgets;
	put_panel(&img, (t_info){100, 0, WIN_W - 100, 75, "#FFFFFF"});
	put_xpm(&img, (t_info){130, 28, xpm[8].width, xpm[8].height, &xpm[8]});
	put_glyphs(fdf, fdf->file.name, (t_info){175, 26, 0, 0, "#757575"});
	put_xpm(&img, (t_info){1713, 20, xpm[9].width, xpm[9].height, &xpm[9]});
	put_xpm(&img, (t_info){1723, 6, xpm[10].width, xpm[10].height, &xpm[10]});
	count = ft_itoa(fdf->file.screenshot);
	put_glyphs(fdf, count, (t_info){1730 - ((ft_strlen(count) - 1) * 5),
		6, 0, 0, "#FFFFFF"});
	put_xpm(&img, (t_info){1781, 30, xpm[12].width, xpm[12].height, &xpm[12]});
	put_xpm(&img, (t_info){1850, 13, xpm[14].width, xpm[14].height, &xpm[14]});
	put_xpm(&img, (t_info){1875, 13, xpm[15].width, xpm[15].height, &xpm[15]});
	free(count);
}

void	put_side(t_fdf *fdf)
{
	t_img	img;
	t_img	*xpm;

	img = fdf->mlx.img;
	xpm = fdf->widgets;
	put_panel(&img, (t_info){0, 0, 100, WIN_H, "#292D39"});
	put_xpm(&img, (t_info){23, 19, xpm[0].width, xpm[0].height, &xpm[0]});
	put_xpm(&img, (t_info){34, 105, xpm[1].width, xpm[1].height, &xpm[1]});
	put_xpm(&img, (t_info){34, 205, xpm[2].width, xpm[2].height, &xpm[2]});
	put_xpm(&img, (t_info){34, 305, xpm[3].width, xpm[3].height, &xpm[3]});
	put_xpm(&img, (t_info){34, 405, xpm[4].width, xpm[4].height, &xpm[4]});
	put_xpm(&img, (t_info){34, 505, xpm[5].width, xpm[5].height, &xpm[5]});
	put_xpm(&img, (t_info){34, 605, xpm[6].width, xpm[6].height, &xpm[6]});
	put_xpm(&img, (t_info){34, 705, xpm[7].width, xpm[7].height, &xpm[7]});
}

void	put_map(t_fdf *fdf)
{
	t_map	map;
	t_point	point;
	int		x;
	int		y;

	map = fdf->map;
	y = -1;
	while (++y < map.height)
	{
		x = -1;
		while (++x < map.width)
		{
			point = set_transform(map.grid[y][x], fdf);
			if (x + 1 < map.width)
				put_line(point, set_transform(map.grid[y][x + 1], fdf), fdf);
			if (y + 1 < map.height)
				put_line(point, set_transform(map.grid[y + 1][x], fdf), fdf);
		}
	}
}

void	put_win(t_mlx mlx)
{
	mlx_put_image_to_window(mlx.ctx, mlx.win, mlx.img.img, 0, 0);
}

void	del_map(t_img *img)
{
	char	*dst;
	int		y;

	y = MAP_Y - 1;
	while (++y < WIN_H)
	{
		dst = img->addr + y * img->line_len + MAP_X * (img->bpp / 8);
		ft_memset(dst, 0, (WIN_W - MAP_X) * (img->bpp / 8));
	}
}
