/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ucho <ucho@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 18:05:51 by ucho              #+#    #+#             */
/*   Updated: 2025/01/24 17:05:59 by ucho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

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

size_t	ft_strlen(const char *s)
{
	size_t	len;

	len = 0;
	while (*s)
	{
		len++;
		s++;
	}
	return (len);
}

char	*ft_strcpy(char *dest, const char *src)
{
	char	*ptr;

	ptr = dest;
	while (*src)
		*dest++ = *src++;
	*dest = '\0';
	return (ptr);
}

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

void	join_buffer(char **buffer, char *source)
{
	char	*update;
	char	*backup;
	size_t	len;

	if (!buffer || !source)
		return ;
	backup = *buffer;
	len = 0;
	if (backup)
		len = ft_strlen(backup);
	update = (char *)malloc(len + ft_strlen(source) + 1);
	if (!update)
	{
		if (backup)
			free(backup);
		*buffer = NULL;
		return ;
	}
	if (backup)
		ft_strcpy(update, backup);
	ft_strcpy(update + len, source);
	update[len + ft_strlen(source)] = '\0';
	*buffer = update;
	if (backup)
		free(backup);
}
