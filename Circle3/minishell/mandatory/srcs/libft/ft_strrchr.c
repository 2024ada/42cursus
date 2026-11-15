/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ucho <ucho@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 11:23:58 by ucho              #+#    #+#             */
/*   Updated: 2026/01/29 04:25:26 by ucho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*index;
	char	value;

	index = 0;
	value = (char)c;
	while (*s)
	{
		if (*s == value)
			index = (char *)s;
		s++;
	}
	if (*s == value)
		index = (char *)s;
	return (index);
}
