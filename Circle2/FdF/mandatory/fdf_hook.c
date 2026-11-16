/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   function07.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ucho <ucho@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 15:11:17 by ucho              #+#    #+#             */
/*   Updated: 2025/08/19 11:46:56 by ucho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	get_key(t_fdf *fdf, int code)
{
	int	index;

	index = 0;
	while (index < KEY_COUNT)
	{
		if (fdf->keys[index].code == code)
			return (index);
		index++;
	}
	return (-1);
}

int	close_hook(void *param)
{
	t_fdf	*fdf;
	int		index;

	fdf = (t_fdf *)param;
	mlx_loop_end(fdf->mlx.ctx);
	mlx_destroy_image(fdf->mlx.ctx, fdf->mlx.img.img);
	index = -1;
	while (++index < WIDGETS_COUNT)
	{
		if (fdf->widgets[index].img)
			mlx_destroy_image(fdf->mlx.ctx, fdf->widgets[index].img);
	}
	index = -1;
	mlx_destroy_window(fdf->mlx.ctx, fdf->mlx.win);
	mlx_destroy_display(fdf->mlx.ctx);
	free(fdf->mlx.ctx);
	free_raw(fdf->map.raw);
	free_matrix(fdf->map.grid, 0);
	exit(0);
	return (0);
}

static int	set_hook(void *param)
{
	t_fdf	*fdf;

	fdf = (t_fdf *)param;
	run_projection(fdf, 0);
	run_scaling(fdf, 0);
	run_translation(fdf, 0);
	run_rotation(fdf, 0);
	run_capture(fdf, 0);
	run_exit(fdf, 0);
	return (0);
}

int	loop_hook(void *param)
{
	t_fdf	*fdf;

	fdf = (t_fdf *)param;
	if (fdf->gui.popup[0] == FALSE)
	{
		set_hook(fdf);
		put_menus(fdf, fdf->widgets, fdf->gui);
		put_alert(fdf);
		del_map(&fdf->mlx.img);
		put_map(fdf);
		if (fdf->gui.popup[3])
		{
			save_ppm(fdf->file, fdf->mlx.img);
			fdf->file.screenshot++;
			fdf->keys[get_key(fdf, KEY_P)].is_pressed = FALSE;
			fdf->gui.popup[3] = FALSE;
		}
		if (fdf->gui.exit[1] == TRUE)
			put_exit(fdf);
	}
	else
		put_popup(fdf);
	put_win(fdf->mlx);
	return (0);
}
