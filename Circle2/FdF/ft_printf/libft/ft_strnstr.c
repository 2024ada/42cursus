/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ucho <ucho@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 11:24:44 by ucho              #+#    #+#             */
/*   Updated: 2024/10/16 12:16:46 by ucho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	char	*b_ptr;
	char	*l_ptr;
	size_t	size;

	if (!*little)
		return ((char *)big);
	size = len;
	while (*big && len)
	{
		b_ptr = (char *)big;
		l_ptr = (char *)little;
		size = len;
		while (*b_ptr && *l_ptr && (*b_ptr == *l_ptr) && size)
		{
			b_ptr++;
			l_ptr++;
			size--;
		}
		if (!*l_ptr)
			return ((char *)big);
		big++;
		len--;
	}
	return (NULL);
}
