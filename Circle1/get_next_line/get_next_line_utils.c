/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ucho <ucho@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 18:05:05 by ucho              #+#    #+#             */
/*   Updated: 2025/01/24 15:24:47 by ucho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

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

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*result;
	size_t	len;

	if (!s1 || !s2)
		return (NULL);
	len = ft_strlen(s1) + ft_strlen(s2);
	result = (char *)malloc(len + 1);
	if (!result)
		return (NULL);
	ft_strcpy(result, s1);
	ft_strcpy(result + ft_strlen(s1), s2);
	result[len] = '\0';
	return (result);
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
