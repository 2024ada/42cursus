/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_free.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ucho <ucho@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 15:11:17 by ucho              #+#    #+#             */
/*   Updated: 2025/08/19 16:39:24 by ucho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	free_matrix(void *row, size_t offset)
{
	char	*col;
	void	*ptr;

	if (!row)
		return ;
	col = (char *)row + offset;
	while (*(void **)col)
	{
		ptr = *(void **)col;
		free(ptr);
		col += sizeof(void *);
	}
	free(row);
}

void	free_raw(t_raw *raw)
{
	t_raw	*tmp;

	while (raw)
	{
		tmp = raw->next;
		free_matrix(raw->strs, 0);
		free(raw);
		raw = tmp;
	}
}

void	free_palette(t_xpm *map)
{
	t_xpm	*tmp;

	while (map)
	{
		tmp = map->next;
		free(map->key);
		free(map);
		map = tmp;
	}
}

void	free_input(int fd)
{
	(void)get_next_line(-42);
	close(fd);
}
