/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   function01-1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ucho <ucho@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 15:11:17 by ucho              #+#    #+#             */
/*   Updated: 2025/08/19 11:38:58 by ucho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static const char	*get_z(const char *z)
{
	if (*z == '+' || *z == '-')
		z++;
	while (*z >= '0' && *z <= '9')
		z++;
	while (*z == ' ' || *z == '\n')
		z++;
	return (z);
}

int	is_valid_map(const char *z, unsigned int *color)
{
	const char	*hex;

	*color = 0;
	z = get_z(z);
	if (*z == '\0')
		return (TRUE);
	if (ft_strncmp(z, ",0x", 3) != 0)
		return (FALSE);
	z += 3;
	if (!((*z >= '0' && *z <= '9')
			|| (*z >= 'A' && *z <= 'F') || (*z >= 'a' && *z <= 'f')))
		return (FALSE);
	hex = z;
	while ((*z >= '0' && *z <= '9')
		|| (*z >= 'A' && *z <= 'F') || (*z >= 'a' && *z <= 'f'))
		z++;
	while (*z == ' ' || *z == '\n')
		z++;
	if (*z != '\0')
		return (FALSE);
	*color = str_to_hex(hex);
	return (TRUE);
}

static int	get_point(t_map *map, t_raw *raw, t_point **grid, t_point point)
{
	int	x;
	int	y;
	int	z;

	x = (int)point.x;
	y = (int)point.y;
	if (!is_valid_map(raw->strs[x], &grid[y][x].color))
		return (FALSE);
	z = ft_atoi(raw->strs[x]);
	grid[y][x].x = (float)x - (((float)map->width - 1.0f) * 0.5f);
	grid[y][x].y = (float)y - (((float)map->height - 1.0f) * 0.5f);
	grid[y][x].z = (float)z - ((float)map->depth * 0.5f);
	if (grid[y][x].color == 0x000000 || grid[y][x].color > 0xFFFFFF)
		grid[y][x].color = 0x00BABC;
	return (TRUE);
}

static int	get_row(t_map *map, t_raw *raw, t_point **grid, int y)
{
	int	x;

	grid[y] = malloc(sizeof(t_point) * map->width);
	if (!grid[y])
		return (0);
	x = -1;
	while (++x < raw->width)
	{
		if (!get_point(map, raw, grid, (t_point){x, y, 0, 0}))
		{
			free(grid[y]);
			grid[y] = NULL;
			return (0);
		}
	}
	return (1);
}

t_point	**get_grid(t_map *map)
{
	t_raw	*raw;
	t_point	**grid;
	int		y;

	raw = map->raw;
	grid = malloc(sizeof(t_point *) * (map->height + 1));
	if (!grid)
		return (NULL);
	y = 0;
	while (raw)
	{
		if (raw->width > 0)
		{
			if (!get_row(map, raw, grid, y))
				return (free_matrix(grid, 0), NULL);
			y++;
		}
		raw = raw->next;
	}
	grid[y] = NULL;
	return (grid);
}
