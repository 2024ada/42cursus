/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ucho <ucho@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 11:23:44 by ucho              #+#    #+#             */
/*   Updated: 2026/07/08 13:23:16 by ucho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

char	*ft_strchr(const char *s, int c)
{
	char	value;

	if (s)
	{
		value = (char)c;
		while (*s)
		{
			if (*s == value)
				return ((char *)s);
			s++;
		}
		if (*s == value)
			return ((char *)s);
	}
	return (NULL);
}
