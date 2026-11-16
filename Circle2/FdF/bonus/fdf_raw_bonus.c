/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_raw_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ucho <ucho@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 15:11:17 by ucho              #+#    #+#             */
/*   Updated: 2025/08/19 16:40:00 by ucho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

static size_t	get_strslen(char **strs)
{
	size_t	len;

	len = 0;
	while (strs[len])
		len++;
	return (len);
}

static t_raw	*get_node(char *line)
{
	t_raw	*new;
	size_t	len;

	new = malloc(sizeof(t_raw));
	if (!new)
		return (NULL);
	ft_bzero(new, sizeof(t_raw));
	new->strs = ft_split(line, ' ');
	if (!new->strs)
		return (free(new), NULL);
	len = get_strslen(new->strs);
	if (len > INT_MAX)
		return (free_matrix(new->strs, 0), free(new), NULL);
	new->width = len;
	new->next = NULL;
	return (new);
}

static int	add_node(t_raw **head, char *line, int *width)
{
	t_raw	*new;
	t_raw	*cur;

	new = get_node(line);
	if (!new)
		return (0);
	if (new->width > 0)
	{
		if (!*width)
			*width = new->width;
		else if (new->width != *width)
			return (free_matrix(new->strs, 0), free(new),
				put_error("Error: Invalid map\n"));
	}
	if (!*head)
		*head = new;
	else
	{
		cur = *head;
		while (cur->next)
			cur = cur->next;
		cur->next = new;
	}
	return (1);
}

t_raw	*get_input(int input, t_map *map)
{
	char	*line;
	t_raw	*raw;
	size_t	len;

	raw = NULL;
	line = get_next_line(input);
	if (!line)
	{
		(free_input(input), put_error("Error: File is empty or unreadable\n"));
		return (NULL);
	}
	while (line)
	{
		len = ft_strlen(line);
		if (len > 0 && line[len - 1] == '\n')
			line[len - 1] = '\0';
		if (!add_node(&raw, line, &map->width))
		{
			(free(line), free_raw(raw), free_input(input));
			return (NULL);
		}
		free(line);
		line = get_next_line(input);
	}
	return (raw);
}

t_raw	*get_raw(t_map *map, char *name)
{
	int		input;
	t_raw	*raw;

	map->width = 0;
	input = set_input(name);
	raw = get_input(input, map);
	if (raw)
		free_input(input);
	if (!map->width)
	{
		if (raw)
			free_raw(raw);
		put_error("Error: Invalid map\n");
		return (NULL);
	}
	return (raw);
}
