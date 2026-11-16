/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_view_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ucho <ucho@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 15:11:17 by ucho              #+#    #+#             */
/*   Updated: 2025/08/19 14:14:28 by ucho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

static void	set_range(t_map map, t_view *view)
{
	t_point	point;

	point = map.grid[0][0];
	view->min_x = point.x;
	view->min_y = point.y;
	set_isometric(map.projection, &view->min_x, &view->min_y, point.z);
	view->max_x = view->min_x;
	view->max_y = view->min_y;
}

static void	get_range(t_map map, t_view *view)
{
	int		x;
	int		y;
	float	temp_x;
	float	temp_y;

	y = -1;
	while (++y < map.height)
	{
		x = -1;
		while (++x < map.width)
		{
			temp_x = map.grid[y][x].x;
			temp_y = map.grid[y][x].y;
			set_isometric(map.projection, &temp_x, &temp_y, map.grid[y][x].z);
			view->min_x = fminf(temp_x, view->min_x);
			view->max_x = fmaxf(temp_x, view->max_x);
			view->min_y = fminf(temp_y, view->min_y);
			view->max_y = fmaxf(temp_y, view->max_y);
		}
	}
}

void	set_view(t_fdf *fdf)
{
	t_view	*view;
	float	scale_x;
	float	scale_y;
	float	dx;
	float	dy;

	view = &fdf->view;
	set_range(fdf->map, view);
	get_range(fdf->map, view);
	dx = fmaxf(view->max_x - view->min_x, 1.0f);
	dy = fmaxf(view->max_y - view->min_y, 1.0f);
	scale_x = (1545.0f - 50.0f) / dx;
	scale_y = (1005.0f - 50.0f) / dy;
	view->scale = fminf(scale_x, scale_y);
	view->scale_max = view->scale * 20.0f;
	view->scale_min = view->scale * 0.1f;
	view->ofs_max_x = (int)((dx * view->scale_max) + 1545.0f);
	view->ofs_max_y = (int)((dy * view->scale_max) + 1005.0f);
	view->mid_x = (view->min_x + view->max_x) * 0.5f;
	view->mid_y = (view->min_y + view->max_y) * 0.5f;
	view->ofs_x = (int)((1545.0f * 0.5f + 375.0f) - view->mid_x * view->scale);
	view->ofs_y = (int)((1005.0f * 0.5f + 75.0f) - view->mid_y * view->scale);
	view->rot_x = 0.0f;
	view->rot_y = 0.0f;
	view->rot_z = 0.0f;
}

void	set_gui(t_fdf *fdf)
{
	const char	*menu[] = {"Isometric", "Orthographic", "Zoom In", "Zoom Out",
		"Move Up", "Move Down", "Move Left", "Move Right", "Rotate X",
		"Rotate Y", "Rotate Z", "Take Screenshot"};
	const char	*highlight[] = {"#666E80", "#FFFFFF"};
	const int	layout[] = {0, 2, 4, 8, 11, 12};

	ft_memset(fdf->gui.hover, 0, sizeof(fdf->gui.hover));
	ft_memset(fdf->gui.popup, 0, sizeof(fdf->gui.popup));
	ft_memset(fdf->gui.exit, 0, sizeof(fdf->gui.exit));
	ft_memcpy(fdf->gui.menu, menu, sizeof(fdf->gui.menu));
	ft_memcpy(fdf->gui.highlight, highlight, sizeof(fdf->gui.highlight));
	ft_memcpy(fdf->gui.layout, layout, sizeof(fdf->gui.layout));
}
