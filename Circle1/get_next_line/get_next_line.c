/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ucho <ucho@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 15:07:58 by ucho              #+#    #+#             */
/*   Updated: 2025/01/24 17:03:58 by ucho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char	*buffer = NULL;
	char		*raw;
	int			scanned;
	int			idx;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	raw = (char *)malloc(BUFFER_SIZE + 1);
	if (!raw)
		return (NULL);
	while (1)
	{
		scanned = read(fd, raw, BUFFER_SIZE);
		if (scanned < 0)
			return (set_err(&buffer, &raw));
		raw[scanned] = '\0';
		modify_buffer(&buffer, raw, 1);
		idx = is_nl(buffer);
		if (idx >= 0)
			return (set_nl(&buffer, &raw, idx));
		if (scanned == 0)
			return (set_eof(&buffer, &raw));
	}
}

int	is_nl(char *buffer)
{
	int	idx;

	if (!buffer)
		return (-1);
	idx = 0;
	while (buffer[idx])
	{
		if (buffer[idx] == '\n')
			return (idx);
		idx++;
	}
	return (-1);
}

char	*set_err(char **buffer, char **raw)
{
	free(*raw);
	*raw = NULL;
	free(*buffer);
	*buffer = NULL;
	return (NULL);
}

char	*set_nl(char **buffer, char **raw, int idx)
{
	char	*line;

	line = ft_strndup(*buffer, idx + 1);
	modify_buffer(buffer, *buffer + idx + 1, 0);
	free(*raw);
	*raw = NULL;
	return (line);
}

char	*set_eof(char **buffer, char **raw)
{
	char	*line;

	free(*raw);
	*raw = NULL;
	if (*buffer && ft_strlen(*buffer) > 0)
	{
		line = ft_strndup(*buffer, ft_strlen(*buffer));
		free(*buffer);
		*buffer = NULL;
		return (line);
	}
	free(*buffer);
	*buffer = NULL;
	return (NULL);
}
