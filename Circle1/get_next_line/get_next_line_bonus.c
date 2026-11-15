/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ucho <ucho@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 18:05:46 by ucho              #+#    #+#             */
/*   Updated: 2025/01/24 17:04:44 by ucho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*get_next_line(int fd)
{
	static t_fd_list	*buffers = NULL;
	t_fd_list			*new;
	char				*raw;
	int					scanned;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	new = add_new(&buffers, fd);
	if (!new)
		return (NULL);
	raw = (char *)malloc(BUFFER_SIZE + 1);
	if (!raw)
		return (set_err(&buffers, new, &raw));
	while (1)
	{
		scanned = read(new->fd, raw, BUFFER_SIZE);
		if (scanned < 0)
			return (set_err(&buffers, new, &raw));
		raw[scanned] = '\0';
		join_buffer(&new->buffer, raw);
		if (is_nl(new->buffer) >= 0)
			return (set_nl(&new->buffer, &raw, is_nl(new->buffer)));
		if (scanned == 0)
			return (set_eof(&buffers, new, &raw));
	}
}

char	*set_err(t_fd_list **buffers, t_fd_list *new, char **raw)
{
	t_fd_list	*backup;
	t_fd_list	**target;

	free(*raw);
	*raw = NULL;
	free(new->buffer);
	new->buffer = NULL;
	target = buffers;
	while (*target)
	{
		if ((*target)->fd == new->fd)
		{
			backup = *target;
			*target = backup->next;
			free(backup->buffer);
			free(backup);
			break ;
		}
		target = &((*target)->next);
	}
	return (NULL);
}

t_fd_list	*add_new(t_fd_list **buffers, int fd)
{
	t_fd_list	*new;
	t_fd_list	*raw;

	raw = *buffers;
	while (raw)
	{
		if (raw->fd == fd)
			return (raw);
		raw = raw->next;
	}
	new = malloc(sizeof(t_fd_list));
	if (!new)
		return (NULL);
	new->fd = fd;
	new->buffer = NULL;
	new->next = *buffers;
	*buffers = new;
	return (new);
}

char	*set_nl(char **buffer, char **raw, int idx)
{
	char	*line;
	char	*update;

	line = ft_strndup(*buffer, idx + 1);
	if (!line)
		return (NULL);
	update = ft_strndup(*buffer + idx + 1, ft_strlen(*buffer + idx + 1));
	if (!update)
	{
		free(line);
		return (NULL);
	}
	free(*buffer);
	*buffer = update;
	free(*raw);
	*raw = NULL;
	return (line);
}

char	*set_eof(t_fd_list **buffers, t_fd_list *new, char **raw)
{
	char		*line;
	t_fd_list	*backup;
	t_fd_list	**target;

	line = NULL;
	free(*raw);
	*raw = NULL;
	if (new->buffer && ft_strlen(new->buffer) > 0)
		line = ft_strndup(new->buffer, ft_strlen(new->buffer));
	free(new->buffer);
	new->buffer = NULL;
	target = buffers;
	while (*target)
	{
		if ((*target)->fd == new->fd)
		{
			backup = *target;
			*target = backup->next;
			free(backup->buffer);
			free(backup);
			break ;
		}
		target = &((*target)->next);
	}
	return (line);
}
