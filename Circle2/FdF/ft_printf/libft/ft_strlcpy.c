/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ucho <ucho@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 11:22:43 by ucho              #+#    #+#             */
/*   Updated: 2024/10/16 00:56:32 by ucho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

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
