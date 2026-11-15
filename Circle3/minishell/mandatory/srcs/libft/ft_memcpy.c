/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ucho <ucho@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 11:22:25 by ucho              #+#    #+#             */
/*   Updated: 2026/01/29 04:25:59 by ucho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_libft.h"

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
