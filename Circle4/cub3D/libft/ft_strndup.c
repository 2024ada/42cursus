/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ucho <ucho@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 20:54:35 by ucho              #+#    #+#             */
/*   Updated: 2026/07/08 13:23:08 by ucho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

char	*ft_strndup(const char *s, size_t n)
{
	char	*dest;
	char	*ptr;

	if (ft_strlen(s) < n)
		n = ft_strlen(s);
	dest = (char *)ft_xmalloc(n + 1);
	ptr = dest;
	while (n--)
		*(dest++) = *(s++);
	*dest = '\0';
	return (ptr);
}
