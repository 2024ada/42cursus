/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_menu_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ucho <ucho@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 15:11:17 by ucho              #+#    #+#             */
/*   Updated: 2025/08/19 14:14:04 by ucho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

static void	put_menu(t_fdf *fdf, int offset, int y)
{
	t_img	*xpm;
	char	*name;
	char	*color;
	int		hover;

	xpm = fdf->widgets;
	name = fdf->gui.menu[offset];
	hover = fdf->gui.hover[offset];
	color = fdf->gui.highlight[hover];
	put_glyphs(fdf, name, (t_info){157, y, 0, 0, color});
	put_xpm(&fdf->mlx.img, (t_info){128, y + 3,
		xpm[21 + (offset * 2) + hover].width,
		xpm[21 + (offset * 2) + hover].height,
		&xpm[21 + (offset * 2) + hover]});
	if (37 <= 21 + (offset * 2) + hover && 21 + (offset * 2) + hover <= 42)
		put_xpm(&fdf->mlx.img, (t_info){294, y + 4,
			xpm[45 + hover].width,
			xpm[45 + hover].height,
			&xpm[45 + hover]});
	put_xpm(&fdf->mlx.img, (t_info){322, y + 4,
		xpm[45 + hover].width,
		xpm[45 + hover].height,
		&xpm[45 + hover]});
}

static void	put_keyboard(t_fdf *fdf, t_gui gui)
{
	t_img	*xpm;
	int		*hover;

	xpm = fdf->widgets;
	hover = gui.hover;
	put_glyphs(fdf, "i", (t_info){332, 144, 0, 0, gui.highlight[hover[0]]});
	put_glyphs(fdf, "o", (t_info){329, 186, 0, 0, gui.highlight[hover[1]]});
	put_glyphs(fdf, "+", (t_info){329, 285, 0, 0, gui.highlight[hover[2]]});
	put_glyphs(fdf, "-", (t_info){331, 327, 0, 0, gui.highlight[hover[3]]});
	put_xpm(&fdf->mlx.img, (t_info){331, 432, xpm[47 + gui.hover[4]].width,
		xpm[47 + hover[4]].height, &xpm[47 + hover[4]]});
	put_xpm(&fdf->mlx.img, (t_info){331, 476, xpm[49 + hover[5]].width,
		xpm[49 + hover[5]].height, &xpm[49 + hover[5]]});
	put_xpm(&fdf->mlx.img, (t_info){328, 524, xpm[51 + hover[6]].width,
		xpm[51 + hover[6]].height, &xpm[51 + hover[6]]});
	put_xpm(&fdf->mlx.img, (t_info){328, 568, xpm[53 + hover[7]].width,
		xpm[53 + hover[7]].height, &xpm[53 + hover[7]]});
	put_glyphs(fdf, "w", (t_info){300, 654, 0, 0, gui.highlight[hover[8]]});
	put_glyphs(fdf, "s", (t_info){331, 654, 0, 0, gui.highlight[hover[8]]});
	put_glyphs(fdf, "a", (t_info){301, 698, 0, 0, gui.highlight[hover[9]]});
	put_glyphs(fdf, "d", (t_info){329, 698, 0, 0, gui.highlight[hover[9]]});
	put_glyphs(fdf, "q", (t_info){301, 742, 0, 0, gui.highlight[hover[10]]});
	put_glyphs(fdf, "e", (t_info){330, 742, 0, 0, gui.highlight[hover[10]]});
	put_glyphs(fdf, "p", (t_info){330, 838, 0, 0, gui.highlight[hover[11]]});
}

void	put_menus(t_fdf *fdf, t_img *xpm, t_gui gui)
{
	int			y;
	int			index;
	int			count;
	int			offset;

	put_panel(&fdf->mlx.img, (t_info){100, 75, 275, WIN_H - 75, "#1E212A"});
	index = -1;
	y = 102;
	while (++index < CATEGORY_COUNT)
	{
		put_xpm(&fdf->mlx.img,
			(t_info){130, y, xpm[16 + index].width,
			xpm[16 + index].height, &xpm[16 + index]});
		count = -1;
		while (++count < gui.layout[index + 1] - gui.layout[index])
		{
			offset = gui.layout[index] + count;
			put_menu(fdf, offset, y + 40 + (count * 44));
		}
		y += 141 + (44 * (gui.layout[index + 1] - gui.layout[index] - 2));
	}
	put_keyboard(fdf, fdf->gui);
	put_xpm(&fdf->mlx.img, (t_info){1781, 30,
		xpm[12 + fdf->gui.exit[0]].width,
		xpm[12 + fdf->gui.exit[0]].height, &xpm[12 + fdf->gui.exit[0]]});
}
