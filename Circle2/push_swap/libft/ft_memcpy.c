/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ucho <ucho@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 11:22:25 by ucho              #+#    #+#             */
/*   Updated: 2024/10/15 23:34:57 by ucho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char	*buffer;
	unsigned char	*ptr;

	if (dest == NULL && src == NULL)
		return (NULL);
	buffer = (unsigned char *)dest;
	ptr = (unsigned char *)src;
	while (n)
	{
		*(buffer++) = *(ptr++);
		n--;
	}
	return (dest);
}
