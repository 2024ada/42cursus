/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ucho <ucho@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 11:23:44 by ucho              #+#    #+#             */
/*   Updated: 2024/10/16 12:13:05 by ucho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	char	value;

	value = (char)c;
	while (*s)
	{
		if (*s == value)
			return ((char *)s);
		s++;
	}
	if (*s == value)
		return ((char *)s);
	return (0);
}
