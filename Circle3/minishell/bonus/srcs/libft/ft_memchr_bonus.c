/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ucho <ucho@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 11:24:25 by ucho              #+#    #+#             */
/*   Updated: 2026/01/29 04:22:18 by ucho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_libft_bonus.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*buffer;
	unsigned char	value;

	buffer = (unsigned char *)s;
	value = (char)c;
	while (n)
	{
		if (*buffer == value)
			return ((void *)buffer);
		buffer++;
		n--;
	}
	return (NULL);
}
