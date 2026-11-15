/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ucho <ucho@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 11:22:43 by ucho              #+#    #+#             */
/*   Updated: 2026/01/29 04:25:33 by ucho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	char			*ptr;

	ptr = (char *)src;
	if (size == 0)
		return (ft_strlen(src));
	while (size > 1 && *src)
	{
		*(dst++) = *(src++);
		size--;
	}
	*dst = '\0';
	return (ft_strlen(ptr));
}
