/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ada <ada@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 18:05:05 by ucho              #+#    #+#             */
/*   Updated: 2025/05/27 06:14:50 by ada              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strndup(const char *s, size_t n)
{
	char	*dest;
	char	*ptr;

	if (ft_strlen(s) < n)
		n = ft_strlen(s);
	dest = (char *)malloc(n + 1);
	if (dest == NULL)
		return (NULL);
	ptr = dest;
	while (n)
	{
		*(dest++) = *(s++);
		n--;
	}
	*dest = '\0';
	return (ptr);
}

void	modify_buffer(char **buffer, char *source, int is_update)
{
	char	*backup;

	if (!buffer || !source)
		return ;
	backup = *buffer;
	if (is_update && *buffer)
		*buffer = ft_strjoin(*buffer, source);
	else
		*buffer = ft_strndup(source, ft_strlen(source));
	if (!*buffer)
	{
		*buffer = backup;
		return ;
	}
	free(backup);
}

char	*let_buffer(int fd, char **buffer)
{
	if (fd == -42 && *buffer)
	{
		free(*buffer);
		*buffer = NULL;
	}
	return (NULL);
}
