/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_init_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ucho <ucho@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 15:11:17 by ucho              #+#    #+#             */
/*   Updated: 2025/08/19 14:13:50 by ucho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

void	set_mlx(t_mlx *mlx, t_map map)
{
	mlx->ctx = mlx_init();
	if (!mlx->ctx)
		(free_raw(map.raw), free_matrix(map.grid, 0), exit(1));
	mlx->win = mlx_new_window(mlx->ctx, WIN_W, WIN_H, "FdF");
	if (!mlx->win)
		(free_raw(map.raw), free_matrix(map.grid, 0), exit(1));
	mlx->img.img = mlx_new_image(mlx->ctx, WIN_W, WIN_H);
	if (!mlx->img.img)
		(free_raw(map.raw), free_matrix(map.grid, 0), exit(1));
	mlx->img.addr = mlx_get_data_addr(mlx->img.img, &mlx->img.bpp,
			&mlx->img.line_len, &mlx->img.endian);
	if (!mlx->img.addr || mlx->img.bpp <= 0 || mlx->img.line_len <= 0)
		(free_raw(map.raw), free_matrix(map.grid, 0), exit(1));
	mlx->img.width = WIN_W;
	mlx->img.height = WIN_H;
}

void	set_widgets(t_fdf *fdf, t_map map)
{
	const t_widget	widgets[WIDGETS_COUNT] = {widget00, widget01, widget02,
		widget03, widget04, widget05, widget06, widget07, widget08, widget09,
		widget10, widget11, widget12, widget13, widget14, widget15, widget16,
		widget17, widget18, widget19, widget20, widget21, widget22, widget23,
		widget24, widget25, widget26, widget27, widget28, widget29, widget30,
		widget31, widget32, widget33, widget34, widget35, widget36, widget37,
		widget38, widget39, widget40, widget41, widget42, widget43, widget44,
		widget45, widget46, widget47, widget48, widget49, widget50, widget51,
		widget52, widget53, widget54, widget55, widget56, widget57, widget58};
	const char		**xpm;
	int				index;
	t_img			*widget;

	index = -1;
	while (++index < WIDGETS_COUNT)
	{
		xpm = widgets[index]();
		widget = mlx_xpm_array_to_image(fdf->mlx.ctx, (char **)xpm);
		if (!widget)
			(free_raw(map.raw), free_matrix(map.grid, 0), exit(1));
		fdf->widgets[index] = *widget;
		free(widget);
	}
}

const char	***set_glyphs(const char ***glyphs)
{
	static int	initialized = 0;

	if (!initialized)
	{
		(glyphs00(glyphs), glyphs01(glyphs), glyphs02(glyphs));
		(glyphs03(glyphs), glyphs04(glyphs), glyphs05(glyphs));
		(glyphs06(glyphs), glyphs07(glyphs), glyphs08(glyphs));
		(glyphs09(glyphs), glyphs10(glyphs), glyphs11(glyphs));
		(glyphs12(glyphs), glyphs13(glyphs), glyphs14(glyphs));
		(glyphs15(glyphs), glyphs16(glyphs), glyphs17(glyphs));
		(glyphs18(glyphs), glyphs19(glyphs), glyphs20(glyphs));
		(glyphs21(glyphs), glyphs22(glyphs), glyphs23(glyphs));
		(glyphs24(glyphs), glyphs25(glyphs), glyphs26(glyphs));
		(glyphs27(glyphs), glyphs28(glyphs), glyphs29(glyphs));
		(glyphs30(glyphs), glyphs31(glyphs), glyphs32(glyphs));
		initialized = 1;
	}
	return (glyphs);
}

void	set_keys(t_key *keys)
{
	int	index;

	keys[0].code = 65307;
	keys[1].code = 65362;
	keys[2].code = 65364;
	keys[3].code = 65361;
	keys[4].code = 65363;
	keys[5].code = 61;
	keys[6].code = 45;
	keys[7].code = 119;
	keys[8].code = 115;
	keys[9].code = 97;
	keys[10].code = 100;
	keys[11].code = 113;
	keys[12].code = 101;
	keys[13].code = 114;
	keys[14].code = 105;
	keys[15].code = 111;
	keys[16].code = 112;
	index = 0;
	while (index < KEY_COUNT)
		keys[index++].is_pressed = FALSE;
}
