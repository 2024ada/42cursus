/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalee <nalee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 11:22:25 by ucho              #+#    #+#             */
/*   Updated: 2026/02/12 17:10:51 by nalee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

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
