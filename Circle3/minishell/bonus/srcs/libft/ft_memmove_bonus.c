/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ucho <ucho@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 11:22:33 by ucho              #+#    #+#             */
/*   Updated: 2026/01/29 04:22:14 by ucho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_libft_bonus.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char	*buffer;
	unsigned char	*ptr;

	if (dest == NULL && src == NULL)
		return (NULL);
	if (dest > src && dest < src + n)
	{
		buffer = ((unsigned char *)dest + (n - 1));
		ptr = ((unsigned char *)src + (n - 1));
		while (n)
		{
			*(buffer--) = *(ptr--);
			n--;
		}
		return (dest);
	}
	buffer = (unsigned char *)dest;
	ptr = (unsigned char *)src;
	while (n)
	{
		*(buffer++) = *(ptr++);
		n--;
	}
	return (dest);
}
