/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ucho <ucho@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 11:23:58 by ucho              #+#    #+#             */
/*   Updated: 2026/01/29 04:21:29 by ucho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_libft_bonus.h"

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
