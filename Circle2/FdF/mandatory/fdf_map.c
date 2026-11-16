/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   function01.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ucho <ucho@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 15:11:17 by ucho              #+#    #+#             */
/*   Updated: 2025/08/19 11:37:43 by ucho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	set_dimensions(t_raw *raw, int *min_z, int *max_z)
{
	int			x;
	long long	z;

	x = -1;
	while (++x < raw->width)
	{
		z = ft_atoll(raw->strs[x]);
		if (z < INT_MIN || z > INT_MAX)
			return (0);
		if (z < *min_z)
			*min_z = z;
		if (z > *max_z)
			*max_z = z;
	}
	return (1);
}

int	get_dimensions(t_map *map, t_raw *raw)
{
	int			min_z;
	int			max_z;
	long long	z;

	map->height = 0;
	z = ft_atoll(raw->strs[0]);
	if (z < INT_MIN || z > INT_MAX)
		return (0);
	min_z = z;
	max_z = z;
	while (raw)
	{
		if (raw->width > 0)
		{
			if (!set_dimensions(raw, &min_z, &max_z))
				return (0);
			if (map->height == INT_MAX)
				return (0);
			map->height++;
		}
		raw = raw->next;
	}
	map->depth = (long long)min_z + (long long)max_z;
	return (1);
}

void	set_map(t_map *map, char *name)
{
	map->raw = get_raw(map, name);
	if (!map->raw)
		exit(1);
	if (!get_dimensions(map, map->raw))
	{
		free_raw(map->raw);
		put_error("Error: Invalid map\n");
		exit(1);
	}
	map->projection = ISOMETRIC;
	map->grid = get_grid(map);
	if (!map->grid)
	{
		free_raw(map->raw);
		put_error("Error: Invalid map\n");
		exit(1);
	}
}
