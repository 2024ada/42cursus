/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ucho <ucho@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 15:11:17 by ucho              #+#    #+#             */
/*   Updated: 2025/08/19 14:13:03 by ucho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

void	set_fdf(t_fdf *fdf)
{
	set_map(&fdf->map, fdf->file.name);
	set_mlx(&fdf->mlx, fdf->map);
	set_widgets(fdf, fdf->map);
	set_glyphs(fdf->glyphs);
	set_keys(fdf->keys);
	set_view(fdf);
	set_gui(fdf);
}

void	put_fdf(t_fdf *fdf)
{
	put_top(fdf);
	put_side(fdf);
	put_map(fdf);
	put_win(fdf->mlx);
}

void	run_fdf(t_fdf *fdf)
{
	mlx_hook(fdf->mlx.win, 2, 1, key_press, fdf);
	mlx_hook(fdf->mlx.win, 3, 2, key_release, fdf);
	mlx_hook(fdf->mlx.win, 17, 0, close_hook, fdf);
	mlx_hook(fdf->mlx.win, 6, 64, mouse_move, fdf);
	mlx_mouse_hook(fdf->mlx.win, mouse_click, fdf);
	mlx_loop_hook(fdf->mlx.ctx, loop_hook, fdf);
	mlx_loop(fdf->mlx.ctx);
}

int	main(int argc, char **argv)
{
	t_fdf	fdf;

	if (argc == 1)
	{
		put_error("Error: No map file specified\nUsage: ./fdf <map.fdf>\n");
		exit(EXIT_FAILURE);
	}
	if (argc != 2)
	{
		put_error("Error: Too many arguments\nUsage: ./fdf <map.fdf>\n");
		exit(EXIT_FAILURE);
	}
	fdf.file.name = argv[1];
	fdf.file.screenshot = 0;
	set_fdf(&fdf);
	put_fdf(&fdf);
	run_fdf(&fdf);
	return (0);
}
