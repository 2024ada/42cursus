/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   function12.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ucho <ucho@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 15:11:17 by ucho              #+#    #+#             */
/*   Updated: 2025/08/19 11:48:35 by ucho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_point	set_transform(t_point point, t_fdf *fdf)
{
	point = set_scale(point, fdf->view.scale);
	point = set_rotate_x(point, fdf->view.rot_x);
	point = set_rotate_y(point, fdf->view.rot_y);
	point = set_rotate_z(point, fdf->view.rot_z);
	set_isometric(fdf->map.projection, &point.x, &point.y, point.z);
	point = set_translate(point, fdf->view.ofs_x, fdf->view.ofs_y);
	return (point);
}

void	set_isometric(int state, float *x, float *y, float z)
{
	float	out_x;
	float	out_y;

	if (state)
	{
		out_x = (*x - *y) * cosf(DEGREE_30);
		out_y = (*x + *y) * sinf(DEGREE_30) - z;
		*x = out_x;
		*y = out_y;
	}
}
