/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   function11.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ucho <ucho@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 15:11:17 by ucho              #+#    #+#             */
/*   Updated: 2025/08/19 11:48:29 by ucho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_point	set_scale(t_point point, float factor)
{
	point.x *= factor;
	point.y *= factor;
	point.z *= factor;
	return (point);
}

t_point	set_rotate_x(t_point point, float angle)
{
	float	y;
	float	z;

	y = point.y * cosf(angle) - point.z * sinf(angle);
	z = point.y * sinf(angle) + point.z * cosf(angle);
	point.y = y;
	point.z = z;
	return (point);
}

t_point	set_rotate_y(t_point point, float angle)
{
	float	x;
	float	z;

	x = point.x * cosf(angle) + point.z * sinf(angle);
	z = -point.x * sinf(angle) + point.z * cosf(angle);
	point.x = x;
	point.z = z;
	return (point);
}

t_point	set_rotate_z(t_point point, float angle)
{
	float	x;
	float	y;

	x = point.x * cosf(angle) - point.y * sinf(angle);
	y = point.x * sinf(angle) + point.y * cosf(angle);
	point.x = x;
	point.y = y;
	return (point);
}

t_point	set_translate(t_point point, int dx, int dy)
{
	float	x;
	float	y;

	x = point.x + (float)dx;
	y = point.y + (float)dy;
	point.x = fminf((float)INT_MAX - 1.0f, fmaxf((float)INT_MIN + 1.0f, x));
	point.y = fminf((float)INT_MAX - 1.0f, fmaxf((float)INT_MIN + 1.0f, y));
	return (point);
}
