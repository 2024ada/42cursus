/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_args.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ucho <ucho@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 19:12:20 by ucho              #+#    #+#             */
/*   Updated: 2025/05/07 14:20:50 by ucho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	append_tokens(char **raw, char **tokens)
{
	char	*tmp;

	while (*tokens)
	{
		tmp = ft_strcjoin(*raw, *tokens++, " ");
		free(*raw);
		if (!tmp)
			return (0);
		*raw = tmp;
	}
	return (1);
}

int	parse_tokens(char **raw, const char *arg)
{
	char	**tok;
	char	**p;

	tok = ft_split(arg, ' ');
	if (!tok || !*tok)
	{
		free(tok);
		return (0);
	}
	if (!is_valid(tok) || !append_tokens(raw, tok))
	{
		p = tok;
		while (*p)
			free(*p++);
		free(tok);
		return (0);
	}
	p = tok;
	while (*p)
		free(*p++);
	free(tok);
	return (1);
}
