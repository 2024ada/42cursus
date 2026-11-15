/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_glob_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ucho <ucho@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 13:04:32 by ucho              #+#    #+#             */
/*   Updated: 2026/01/29 04:26:44 by ucho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	slash_to_star(char *str)
{
	t_idx	i;

	if (!str)
		return ;
	i = -1;
	while (str[++i])
	{
		if (str[i] == '/')
			str[i] = '*';
	}
}

void	star_to_slash(char *tok)
{
	char	quote;
	t_idx	i;

	if (!tok)
		return ;
	i = 0;
	while (tok[i])
	{
		if (tok[i] == '\'' || tok[i] == '"')
		{
			quote = tok[i];
			i++;
			while (tok[i] && tok[i] != quote)
			{
				if (tok[i] == '*')
					tok[i] = '/';
				i++;
			}
			if (tok[i] == quote)
				i++;
		}
		else
			i++;
	}
}

char	*del_quote(const char *str, int *has_quote)
{
	char	*res;
	char	*dst;
	char	quote;

	if (!str)
		return (NULL);
	res = (char *)ft_xmalloc(ft_strlen(str) + 1);
	dst = res;
	while (*str)
	{
		if (*str == '\'' || *str == '"')
		{
			quote = *(str++);
			if (has_quote)
				*has_quote = TRUE;
			while (*str && *str != quote)
				*dst++ = *str++;
			if (*str == quote)
				str++;
		}
		else
			*dst++ = *str++;
	}
	*dst = '\0';
	return (res);
}
