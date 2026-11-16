/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   function09.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ucho <ucho@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 15:11:17 by ucho              #+#    #+#             */
/*   Updated: 2025/08/19 11:47:53 by ucho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static t_xpm	*create_color_node(char *xpm_line, int cpp)
{
	t_xpm	*node;
	char	*hex;

	node = malloc(sizeof(t_xpm));
	if (!node)
		return (NULL);
	node->key = ft_substr(xpm_line, 0, cpp);
	if (!node->key)
	{
		free(node);
		return (NULL);
	}
	hex = ft_strchr(xpm_line + cpp, '#');
	if (ft_strnstr(xpm_line, "None", ft_strlen(xpm_line)))
		node->color = 0xFF000000;
	else if (hex)
		node->color = str_to_hex(hex);
	else
		node->color = 0xFFFFFF;
	node->next = NULL;
	return (node);
}

t_xpm	*parse_palette(char **xpm, int colors, int cpp)
{
	t_xpm	*head;
	t_xpm	*node;
	int		i;

	head = NULL;
	i = 0;
	while (i < colors)
	{
		node = create_color_node(xpm[i], cpp);
		if (!node)
		{
			free_palette(head);
			return (NULL);
		}
		node->next = head;
		head = node;
		i++;
	}
	return (head);
}

unsigned int	get_color(char *symbol, t_xpm *map, int cpp)
{
	while (map)
	{
		if (!ft_strncmp(map->key, symbol, cpp))
			return (map->color);
		map = map->next;
	}
	return (0xFFFFFF);
}

void	put_xpm_pixels(t_img *img, t_xpm *map, char **xpm, int cpp)
{
	int				x;
	int				y;
	char			*line;
	char			*key;
	unsigned int	color;

	y = -1;
	while (++y < img->height)
	{
		line = xpm[y];
		x = -1;
		while (++x < img->width)
		{
			key = ft_substr(line, x * cpp, cpp);
			color = get_color(key, map, cpp);
			mlx_pixel_to_image(img, x, y, color);
			free(key);
		}
	}
}

int	parse_meta(char **xpm, t_meta *meta)
{
	char	**header;

	header = ft_split(xpm[0], ' ');
	if (!header || !header[0] || !header[1] || !header[2] || !header[3])
	{
		free_matrix(header, 0);
		return (0);
	}
	meta->width = ft_atoi(header[0]);
	meta->height = ft_atoi(header[1]);
	meta->size = ft_atoi(header[2]);
	meta->cpp = ft_atoi(header[3]);
	free_matrix(header, 0);
	return (1);
}
