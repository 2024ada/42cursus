/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stradd_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ucho <ucho@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 02:58:57 by ucho              #+#    #+#             */
/*   Updated: 2026/01/29 04:21:57 by ucho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_libft_bonus.h"

void	ft_stradd(char **dst, const char *src)
{
	char	*tmp;

	if (!src || !*src)
		return ;
	if (!*dst)
	{
		*dst = ft_strdup(src);
		return ;
	}
	tmp = ft_strjoin(*dst, src);
	free(*dst);
	*dst = tmp;
}
