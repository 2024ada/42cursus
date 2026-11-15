/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ucho <ucho@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 11:23:01 by ucho              #+#    #+#             */
/*   Updated: 2026/01/29 04:25:36 by ucho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	dst_len;
	size_t	src_len;
	size_t	buffer;

	dst_len = ft_strlen(dst);
	src_len = ft_strlen(src);
	if (size <= dst_len)
		return (size + src_len);
	dst = dst + dst_len;
	buffer = size - dst_len - 1;
	while (buffer && *src)
	{
		*(dst++) = *(src++);
		buffer--;
	}
	*dst = '\0';
	return (dst_len + src_len);
}
