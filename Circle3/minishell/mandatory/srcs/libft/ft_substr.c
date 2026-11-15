/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ucho <ucho@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 11:30:12 by ucho              #+#    #+#             */
/*   Updated: 2026/01/29 04:25:22 by ucho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_libft.h"

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
		substr = (char *)ft_xmalloc(1);
		*substr = '\0';
		return (substr);
	}
	if ((s_len - start) < len)
		sub_len = s_len - start;
	else
		sub_len = len;
	substr = (char *)ft_xmalloc((sub_len) + 1);
	ft_strlcpy(substr, s + start, (sub_len + 1));
	return (substr);
}
