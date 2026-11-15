/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   070_draw_text_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ucho <ucho@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/09 04:51:01 by ucho              #+#    #+#             */
/*   Updated: 2026/07/09 04:51:02 by ucho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D_bonus.h>

#ifdef BONUS

static int	get_font_idx(char c)
{
	if (c >= '0' && c <= '9')
		return (c - '0');
	if (c >= 'A' && c <= 'Z')
		return (10 + c - 'A');
	return (-1);
}

static int	set_text_align(t_app *app, const char *str, t_text text)
{
	t_dim	width;
	t_idx	i;
	t_idx	j;

	width = 0;
	i = 0;
	while (str[i])
	{
		j = get_font_idx(str[i]);
		if (str[i] == ' ')
			width += FONT_SPACE;
		else if (j >= 0)
			width += (int)(app->assets.font[j].size.w * text.scale)
				+ FONT_SPACING;
		i++;
	}
	if (width > 0)
		width -= FONT_SPACING;
	if (text.align == FONT_CENTER)
		return (text.pos.x - width / 2);
	if (text.align == FONT_RIGHT)
		return (text.pos.x - width);
	return (text.pos.x);
}

static void	draw_glyph(t_app *app, t_img *glyph, t_text text)
{
	int		color;
	t_ixy	pixel;
	t_iwh	size;

	if (!glyph || !glyph->img)
		return ;
	size.w = (int)(glyph->size.w * text.scale);
	size.h = (int)(glyph->size.h * text.scale);
	if (size.w <= 0 || size.h <= 0)
		return ;
	pixel.y = -1;
	while (++pixel.y < size.h)
	{
		pixel.x = -1;
		while (++pixel.x < size.w)
		{
			color = get_scaled_pixel(glyph, pixel, size.w, size.h);
			if (!is_transparent_color(color))
				put_pixel(&app->core.screen,
					(t_ixy){text.pos.x + pixel.x,
					text.pos.y + pixel.y}, text.color);
		}
	}
}

static void	draw_text(t_app *app, const char *text, t_text info)
{
	t_pos	x;
	t_idx	i;
	t_idx	j;

	x = set_text_align(app, text, info);
	i = -1;
	while (text[++i])
	{
		j = get_font_idx(text[i]);
		if (text[i] == ' ')
			x += FONT_SPACE;
		else if (j >= 0)
		{
			info.pos.x = x;
			draw_glyph(app, &app->assets.font[j], info);
			x += (int)(app->assets.font[j].size.w * info.scale)
				+ FONT_SPACING;
		}
	}
}

void	draw_number(t_app *app, t_num value, t_text text)
{
	char	*str;

	if (value < 0)
		value = 0;
	str = ft_itoa(value);
	if (!str)
		return ;
	draw_text(app, str, text);
	free(str);
}

#endif
