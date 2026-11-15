/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_lex_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ucho <ucho@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 13:00:27 by ucho              #+#    #+#             */
/*   Updated: 2026/01/29 04:26:36 by ucho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	lex_tok(t_vec *toks, char **val, char *var)
{
	t_tok	tok;

	if (val && *val)
	{
		ft_memset(&tok, 0, sizeof(t_tok));
		tok.val = *val;
		tok.var = var;
		vec_push(toks, &tok);
		*val = NULL;
	}
	else if (var)
		free(var);
	return (TRUE);
}

int	lex_env(t_vec *toks, char **buf, char *var)
{
	char	*tok;
	size_t	len;

	while (*var)
	{
		if (ft_isspace(*var))
			var = lex_space(NULL, toks, buf, var);
		else
		{
			len = ft_strskip(var, ft_isspace, TRUE) - var;
			tok = ft_substr(var, 0, len);
			if (ft_isop(tok))
			{
				ft_stradd(buf, "'");
				ft_stradd(buf, tok);
				ft_stradd(buf, "'");
			}
			else
				ft_stradd(buf, tok);
			free(tok);
			var += len;
		}
	}
	return (TRUE);
}

char	*lex_space(t_shell *shell, t_vec *toks, char **buf, char *input)
{
	lex_tok(toks, buf, NULL);
	while (*input && ft_isspace(*input))
	{
		if (*input == '\n' && shell)
			shell->lines++;
		input++;
	}
	return (input);
}

char	*lex_char(char **buf, char *c)
{
	char	str[2];

	if (!c || !*c)
		return (c);
	str[0] = *c;
	str[1] = '\0';
	ft_stradd(buf, str);
	return (c + 1);
}

void	free_tok(void *elem)
{
	t_tok	*tok;

	tok = (t_tok *)elem;
	if (tok->val)
		free(tok->val);
	if (tok->var)
		free(tok->var);
}
