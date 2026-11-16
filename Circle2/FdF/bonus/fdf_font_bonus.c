/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_font_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ucho <ucho@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 15:11:17 by ucho              #+#    #+#             */
/*   Updated: 2025/08/19 14:13:16 by ucho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

unsigned int	get_pixel_color(t_img *img, int x, int y)
{
	char			*pixel;
	unsigned int	color;
	int				offset;

	if (x < 0 || x >= img->width || y < 0 || y >= img->height)
		return (0);
	offset = y * img->line_len + x * (img->bpp / 8);
	pixel = img->addr + offset;
	color = *(unsigned int *)pixel;
	return (color);
}

static char	**copy_xpm(const char **xpm, t_meta meta)
{
	char	**copy;
	int		x;
	int		y;

	if (!xpm || !xpm[0])
		return (NULL);
	y = 1 + meta.size + meta.height;
	copy = (char **)malloc(sizeof(char *) * (y + 1));
	if (!copy)
		return (NULL);
	x = -1;
	while (++x < y)
	{
		copy[x] = ft_strdup(xpm[x]);
		if (!copy[x])
		{
			copy[x] = NULL;
			free_matrix(copy, 0);
			return (NULL);
		}
	}
	copy[x] = NULL;
	return (copy);
}

static t_color	lerp_color(t_color start, t_color end, float t)
{
	t_color	out;

	out.r = (unsigned char)(start.r * (1.0f - t) + end.r * t);
	out.g = (unsigned char)(start.g * (1.0f - t) + end.g * t);
	out.b = (unsigned char)(start.b * (1.0f - t) + end.b * t);
	return (out);
}

static unsigned int	set_font_color(char *hex_in,
								unsigned int hex_main, unsigned int hex_bg)
{
	t_color			in_color;
	t_color			main_color;
	t_color			bg_color;
	float			alpha;
	t_color			out_color;

	in_color = hex_to_rgb(str_to_hex(hex_in));
	main_color = hex_to_rgb(hex_main);
	bg_color = hex_to_rgb(hex_bg);
	if (str_to_hex(hex_in) == 0x000000)
		return (hex_main);
	alpha = 1.0f - ((float)in_color.r / 255.0f);
	out_color = lerp_color(bg_color, main_color, alpha);
	return (rgb_to_hex(out_color));
}

char	**get_glyphs(const char **xpm, unsigned int fg, unsigned int bg)
{
	char			**result;
	t_meta			meta;
	char			*hex;
	unsigned int	color;

	if (!parse_meta((char **)xpm, &meta))
		return (NULL);
	result = copy_xpm(xpm, meta);
	if (!result)
		return (NULL);
	meta.size++;
	while (meta.size--)
	{
		hex = ft_strchr(result[meta.size] + meta.cpp, '#');
		if (hex)
		{
			color = set_font_color(hex, fg, bg);
			hex = hex_to_str(color);
			if (hex)
				(ft_strlcpy(result[meta.size] + meta.cpp, hex, 8), free(hex));
		}
	}
	return (result);
}
