/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_line_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ucho <ucho@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 15:11:17 by ucho              #+#    #+#             */
/*   Updated: 2025/08/19 14:13:58 by ucho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

static void	put_line_pixels(t_fdf *fdf, int *from, int *size, int *step)
{
	int	condition;
	int	decision;
	int	index;

	condition = size[0] < size[1];
	decision = 2 * size[condition ^ 1] - size[condition];
	index = -1;
	while (++index < size[condition])
	{
		from[condition] += step[condition];
		if (decision < 0)
			decision += 2 * size[condition ^ 1];
		else
		{
			from[condition ^ 1] += step[condition ^ 1];
			decision += 2 * (size[condition ^ 1] - size[condition]);
		}
		if (MAP_X <= from[0] && from[0] <= WIN_W
			&& MAP_Y <= from[1] && from[1] <= WIN_H)
			mlx_pixel_to_image(&(fdf->mlx.img), from[0], from[1], from[2]);
	}
}

void	put_line(t_point start, t_point end, t_fdf *fdf)
{
	int	from[3];
	int	to[2];
	int	step[2];
	int	size[2];

	from[0] = (int)roundf(start.x);
	from[1] = (int)roundf(start.y);
	from[2] = start.color;
	to[0] = (int)roundf(end.x);
	to[1] = (int)roundf(end.y);
	size[0] = abs(to[0] - from[0]);
	size[1] = abs(to[1] - from[1]);
	step[0] = -1;
	step[1] = -1;
	if (from[0] < to[0])
		step[0] = 1;
	if (from[1] < to[1])
		step[1] = 1;
	if (MAP_X <= from[0] && from[0] <= WIN_W
		&& MAP_Y <= from[1] && from[1] <= WIN_H)
		mlx_pixel_to_image(&(fdf->mlx.img), from[0], from[1], from[2]);
	put_line_pixels(fdf, from, size, step);
}
