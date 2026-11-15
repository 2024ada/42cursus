/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ucho <ucho@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 11:14:16 by ucho              #+#    #+#             */
/*   Updated: 2026/01/29 04:22:48 by ucho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_libft_bonus.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void			*result;
	unsigned char	*buffer;
	size_t			len;

	len = nmemb * size;
	if (nmemb != 0 && len / nmemb != size)
		return (NULL);
	result = ft_xmalloc(len);
	buffer = (unsigned char *)result;
	while (len)
	{
		*buffer = 0;
		buffer++;
		len--;
	}
	return (result);
}
