/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   function14.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ucho <ucho@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 15:11:17 by ucho              #+#    #+#             */
/*   Updated: 2025/08/19 11:51:13 by ucho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	run_scaling(t_fdf *fdf, int button)
{
	if (fdf->keys[get_key(fdf, KEY_PLUS)].is_pressed
		|| (button == 1 && fdf->gui.hover[2]))
	{
		if (fdf->view.scale * 1.5f <= fdf->view.scale_max)
			fdf->view.scale *= 1.5f;
	}
	if (fdf->keys[get_key(fdf, KEY_MINUS)].is_pressed
		|| (button == 1 && fdf->gui.hover[3]))
	{
		if (fdf->view.scale / 1.5f >= fdf->view.scale_min)
			fdf->view.scale /= 1.5f;
	}
}

void	run_translation(t_fdf *fdf, int button)
{
	t_view		*view;

	view = &fdf->view;
	if ((fdf->keys[get_key(fdf, KEY_UP)].is_pressed
			|| (button == 1 && fdf->gui.hover[4]))
		&& view->ofs_y - 10 >= -view->ofs_max_y)
		view->ofs_y -= 10;
	if ((fdf->keys[get_key(fdf, KEY_DOWN)].is_pressed
			|| (button == 1 && fdf->gui.hover[5]))
		&& view->ofs_y + 10 <= view->ofs_max_y)
		view->ofs_y += 10;
	if ((fdf->keys[get_key(fdf, KEY_LEFT)].is_pressed
			|| (button == 1 && fdf->gui.hover[6]))
		&& view->ofs_x - 10 >= -view->ofs_max_x)
		view->ofs_x -= 10;
	if ((fdf->keys[get_key(fdf, KEY_RIGHT)].is_pressed
			|| (button == 1 && fdf->gui.hover[7]))
		&& view->ofs_x + 10 <= view->ofs_max_x)
		view->ofs_x += 10;
}

static float	get_rotation(float angle)
{
	if (isnan(angle))
		return (0.0f);
	angle = fmodf(angle, 2.0f * M_PI);
	if (angle < 0)
		angle += 2.0f * M_PI;
	return (angle);
}

static void	set_rotation(float *rot)
{
	if (isnan(*rot))
		*rot = 0.0f;
}

void	run_rotation(t_fdf *fdf, int button)
{
	const float	angle = 5.0f * (M_PI / 180.0f);

	set_rotation(&fdf->view.rot_x);
	set_rotation(&fdf->view.rot_y);
	set_rotation(&fdf->view.rot_z);
	if (fdf->keys[get_key(fdf, KEY_W)].is_pressed
		|| (button == 1 && fdf->gui.hover[8]))
		fdf->view.rot_x = get_rotation(fdf->view.rot_x + angle);
	if (fdf->keys[get_key(fdf, KEY_S)].is_pressed
		|| (button == 3 && fdf->gui.hover[8]))
		fdf->view.rot_x = get_rotation(fdf->view.rot_x - angle);
	if (fdf->keys[get_key(fdf, KEY_A)].is_pressed
		|| (button == 1 && fdf->gui.hover[9]))
		fdf->view.rot_y = get_rotation(fdf->view.rot_y + angle);
	if (fdf->keys[get_key(fdf, KEY_D)].is_pressed
		|| (button == 3 && fdf->gui.hover[9]))
		fdf->view.rot_y = get_rotation(fdf->view.rot_y - angle);
	if (fdf->keys[get_key(fdf, KEY_Q)].is_pressed
		|| (button == 1 && fdf->gui.hover[10]))
		fdf->view.rot_z = get_rotation(fdf->view.rot_z + angle);
	if (fdf->keys[get_key(fdf, KEY_E)].is_pressed
		|| (button == 3 && fdf->gui.hover[10]))
		fdf->view.rot_z = get_rotation(fdf->view.rot_z - angle);
}
