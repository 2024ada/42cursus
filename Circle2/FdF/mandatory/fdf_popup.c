/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   function18.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ucho <ucho@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 15:11:17 by ucho              #+#    #+#             */
/*   Updated: 2025/08/19 11:51:54 by ucho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	put_exit(t_fdf *fdf)
{
	t_img		img;
	t_img		*xpm;
	const char	*colors[] = {"#FFFFFF", "#F5F5F5"};

	img = fdf->mlx.img;
	xpm = fdf->widgets;
	put_panel(&img, (t_info){1760, 75, 160, 40, "#C8C8C8"});
	put_panel(&img, (t_info){1761, 75, 160, 39, "#FFFFFF"});
	put_panel(&img, (t_info){1761, 75, 160, 32,
		(char *)colors[fdf->gui.exit[2]]});
	put_xpm(&img, (t_info){1788, 84, xpm[58].width, xpm[58].height, &xpm[58]});
}

void	put_popup(t_fdf *fdf)
{
	t_img		img;
	t_img		*xpm;
	char		*message;
	const char	*colors[] = {"#00BABC", "#008889"};

	img = fdf->mlx.img;
	xpm = fdf->widgets;
	message = "Would you like to save a screenshot of the current screen?";
	put_panel(&fdf->mlx.img, (t_info){710, 427, 500, 236, "#FFFFFF"});
	put_panel(&fdf->mlx.img, (t_info){728, 469, 193, 9, "#363C49"});
	put_panel(&fdf->mlx.img, (t_info){911, 584, 130, 60, "#BAC0C7"});
	put_panel(&fdf->mlx.img, (t_info){1062, 584, 130, 60,
		(char *)colors[fdf->gui.popup[2]]});
	put_xpm(&img, (t_info){728, 496, xpm[56].width, xpm[56].height, &xpm[56]});
	put_xpm(&img, (t_info){792, 496, xpm[57].width, xpm[57].height, &xpm[57]});
	put_xpm(&img, (t_info){867, 493, xpm[55].width, xpm[55].height, &xpm[55]});
	put_glyphs(fdf, message, (t_info){728, 516, 0, 0, "#000000"});
	put_glyphs(fdf, "CANCEL", (t_info){942, 602, 0, 0, "#FFFFFF"});
	put_glyphs(fdf, "I confirm !", (t_info){1093, 602, 0, 0, "#FFFFFF"});
}

void	put_alert(t_fdf *fdf)
{
	char	*color;
	char	*count;

	color = "#FFFFFF";
	if (fdf->file.screenshot > 0)
	{
		put_xpm(&fdf->mlx.img, (t_info){1723, 6, fdf->widgets[11].width,
			fdf->widgets[11].height, &fdf->widgets[11]});
		count = ft_itoa(fdf->file.screenshot);
		put_glyphs(fdf, count,
			(t_info){1730 - ((ft_strlen(count) - 1) * 5), 6, 0, 0, color});
		free(count);
	}
}
