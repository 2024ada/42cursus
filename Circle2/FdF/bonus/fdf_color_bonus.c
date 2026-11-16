/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_color_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ucho <ucho@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 15:11:17 by ucho              #+#    #+#             */
/*   Updated: 2025/08/19 14:13:10 by ucho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

unsigned int	str_to_hex(const char *hex)
{
	unsigned int	color;
	int				value;

	color = 0;
	if (hex[0] == '#')
		hex++;
	while (*hex)
	{
		color <<= 4;
		if (*hex >= '0' && *hex <= '9')
			value = *hex - '0';
		else if (*hex >= 'A' && *hex <= 'F')
			value = *hex - 'A' + 10;
		else if (*hex >= 'a' && *hex <= 'f')
			value = *hex - 'a' + 10;
		else
			break ;
		color += value;
		hex++;
	}
	return (color);
}

char	*hex_to_str(unsigned int color)
{
	char	*hex;
	char	*radix;
	int		index;

	hex = malloc(sizeof(char) * 8);
	if (!hex)
		return (NULL);
	radix = "0123456789ABCDEF";
	index = 6;
	hex[7] = '\0';
	while (index > 0)
	{
		hex[index] = radix[color & 0xF];
		color >>= 4;
		index--;
	}
	hex[0] = '#';
	return (hex);
}

unsigned int	rgb_to_hex(t_color c)
{
	return (((unsigned int)c.r << 16)
		| ((unsigned int)c.g << 8)
		| (unsigned int)c.b);
}

t_color	hex_to_rgb(unsigned int hex)
{
	t_color	c;

	c.r = (hex >> 16) & 0xFF;
	c.g = (hex >> 8) & 0xFF;
	c.b = hex & 0xFF;
	return (c);
}
