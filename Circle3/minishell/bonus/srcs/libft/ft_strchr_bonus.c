/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ucho <ucho@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 11:23:44 by ucho              #+#    #+#             */
/*   Updated: 2026/01/29 04:21:53 by ucho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_libft_bonus.h"

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
