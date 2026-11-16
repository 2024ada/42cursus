/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_event_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ucho <ucho@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 15:11:17 by ucho              #+#    #+#             */
/*   Updated: 2025/08/19 14:13:12 by ucho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

static void	set_hover(int *hover, int x, int y)
{
	hover[0] = (100 <= x && x < 375 && 133 <= y && y <= 176);
	hover[1] = (100 <= x && x < 375 && 177 <= y && y <= 220);
	hover[2] = (100 <= x && x < 375 && 274 <= y && y <= 317);
	hover[3] = (100 <= x && x < 375 && 318 <= y && y <= 361);
	hover[4] = (100 <= x && x < 375 && 415 <= y && y <= 458);
	hover[5] = (100 <= x && x < 375 && 459 <= y && y <= 502);
	hover[6] = (100 <= x && x < 375 && 503 <= y && y <= 546);
	hover[7] = (100 <= x && x < 375 && 547 <= y && y <= 590);
	hover[8] = (100 <= x && x < 375 && 644 <= y && y <= 687);
	hover[9] = (100 <= x && x < 375 && 688 <= y && y <= 731);
	hover[10] = (100 <= x && x < 375 && 732 <= y && y <= 775);
	hover[11] = (100 <= x && x < 375 && 829 <= y && y <= 872);
}

int	key_press(int keycode, void *param)
{
	t_fdf	*fdf;
	int		index;

	fdf = (t_fdf *)param;
	index = get_key(fdf, keycode);
	if (index != -1)
		fdf->keys[index].is_pressed = 1;
	if (keycode == KEY_ESC)
		close_hook(param);
	return (0);
}

int	key_release(int keycode, void *param)
{
	t_fdf	*fdf;
	int		index;

	fdf = (t_fdf *)param;
	index = get_key(fdf, keycode);
	if (index != -1)
		fdf->keys[index].is_pressed = 0;
	return (0);
}

int	mouse_move(int x, int y, void *param)
{
	t_fdf	*fdf;
	int		hover[12];

	fdf = (t_fdf *)param;
	set_hover(hover, x, y);
	fdf->gui.popup[1] = (911 <= x && x < 1041 && 584 <= y && y <= 644);
	fdf->gui.popup[2] = (1062 <= x && x < 1192 && 584 <= y && y <= 644);
	fdf->gui.exit[0] = (1760 <= x && x < 1920 && 0 <= y && y <= 75);
	fdf->gui.exit[2] = (1760 <= x && x < 1920 && 75 <= y && y <= 115);
	fdf = (t_fdf *)param;
	ft_memcpy(fdf->gui.hover, hover, sizeof(fdf->gui.hover));
	return (0);
}

int	mouse_click(int button, int x, int y, void *param)
{
	t_fdf	*fdf;
	int		hover[12];

	fdf = (t_fdf *)param;
	if (!fdf->gui.popup[0])
	{
		set_hover(hover, x, y);
		run_projection(fdf, button);
		run_scaling(fdf, button);
		run_translation(fdf, button);
		run_rotation(fdf, button);
		run_capture(fdf, button);
		run_exit(fdf, button);
	}
	run_popup(fdf, button);
	return (0);
}
