/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   function16.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ucho <ucho@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 15:11:17 by ucho              #+#    #+#             */
/*   Updated: 2025/08/19 11:51:05 by ucho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	run_projection(t_fdf *fdf, int button)
{
	if (fdf->keys[get_key(fdf, KEY_R)].is_pressed)
		set_view(fdf);
	if (fdf->keys[get_key(fdf, KEY_I)].is_pressed
		|| (button == 1 && fdf->gui.hover[0]))
	{
		fdf->map.projection = ISOMETRIC;
		set_view(fdf);
	}
	if (fdf->keys[get_key(fdf, KEY_O)].is_pressed
		|| (button == 1 && fdf->gui.hover[1]))
	{
		fdf->map.projection = ORTHOGRAPHIC;
		set_view(fdf);
	}
}

void	run_exit(t_fdf *fdf, int button)
{
	if (button != 1)
		return ;
	if ((fdf->gui.exit[1] && !fdf->gui.exit[2]))
		fdf->gui.exit[1] = FALSE;
	else if (!fdf->gui.exit[1] && fdf->gui.exit[0])
		fdf->gui.exit[1] = TRUE;
	else if (fdf->gui.exit[1] && fdf->gui.exit[2])
		close_hook(fdf);
}

void	run_popup(t_fdf *fdf, int button)
{
	if (button == 1 && fdf->gui.popup[1])
		fdf->gui.popup[0] = FALSE;
	if (button == 1 && fdf->gui.popup[2])
	{
		fdf->gui.popup[0] = FALSE;
		fdf->gui.popup[3] = TRUE;
	}
}

void	run_capture(t_fdf *fdf, int button)
{
	if (fdf->keys[get_key(fdf, KEY_P)].is_pressed == TRUE
		|| (button == 1 && fdf->gui.hover[11]))
		fdf->gui.popup[0] = TRUE;
}
