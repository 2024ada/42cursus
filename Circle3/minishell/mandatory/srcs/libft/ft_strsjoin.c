/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsjoin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ucho <ucho@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 18:19:32 by ucho              #+#    #+#             */
/*   Updated: 2026/01/29 04:25:25 by ucho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_libft.h"

char	*ft_strsjoin(char **strs)
{
	char	*res;
	size_t	len;
	size_t	idx;

	if (!strs || !*strs)
		return (NULL);
	len = 0;
	idx = 0;
	while (strs[idx])
		len += ft_strlen(strs[idx++]);
	res = (char *)ft_xmalloc(len + 1);
	res[len] = '\0';
	idx = 0;
	len = 0;
	while (strs[idx])
	{
		ft_strcpy(res + len, strs[idx]);
		len += ft_strlen(strs[idx++]);
	}
	return (res);
}
