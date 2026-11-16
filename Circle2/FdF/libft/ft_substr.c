/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ucho <ucho@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 11:30:12 by ucho              #+#    #+#             */
/*   Updated: 2024/10/16 13:51:48 by ucho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*substr;
	size_t	s_len;
	size_t	sub_len;

	if (!s)
		return (NULL);
	s_len = ft_strlen(s);
	if (start >= s_len)
	{
		substr = (char *)malloc(1);
		if (!substr)
			return (NULL);
		*substr = '\0';
		return (substr);
	}
	if ((s_len - start) < len)
		sub_len = s_len - start;
	else
		sub_len = len;
	substr = (char *)malloc((sub_len) + 1);
	if (!substr)
		return (NULL);
	ft_strlcpy(substr, s + start, (sub_len + 1));
	return (substr);
}
