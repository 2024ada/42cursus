/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ucho <ucho@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 11:30:30 by ucho              #+#    #+#             */
/*   Updated: 2026/01/29 04:21:27 by ucho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_libft_bonus.h"

static char	*ft_strncpy(char *dest, char *src, unsigned int n)
{
	char	*ptr;

	ptr = dest;
	while (n > 0 && *src)
	{
		*(dest++) = *(src++);
		n--;
	}
	while (n)
	{
		*(dest++) = '\0';
		n--;
	}
	return (ptr);
}

static int	is_set(char c, const char *set)
{
	while (*set)
	{
		if (c == *set)
			return (TRUE);
		set++;
	}
	return (FALSE);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*start;
	char	*end;
	char	*buffer;
	size_t	len;

	if (!s1 || !set)
		return (NULL);
	start = (char *)s1;
	end = (char *)s1 + ft_strlen(s1) - 1;
	len = 0;
	while (is_set(*start, set) && *(start++))
		len++;
	while (*start && is_set(*end, set) && *(end--))
		len++;
	buffer = (char *)ft_xmalloc(ft_strlen(s1) - len + 1);
	ft_strncpy(buffer, start, ft_strlen(s1) - len);
	buffer[ft_strlen(s1) - len] = '\0';
	return (buffer);
}
