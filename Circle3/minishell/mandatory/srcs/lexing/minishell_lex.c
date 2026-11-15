/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_lex.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ucho <ucho@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 16:53:01 by ucho              #+#    #+#             */
/*   Updated: 2026/01/29 04:26:34 by ucho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	lex_prompt(t_shell *shell, t_vec *toks, char **raw, char *input)
{
	char	*buf;
	char	quote;
	size_t	lineno;

	lineno = shell->lines;
	(vec_init(toks, sizeof(t_tok), 16, free_tok), buf = NULL);
	while (*input)
	{
		if ((buf && *buf && ft_isdigit(buf[ft_strlen(buf) - 1])
				&& ft_isdigit(*input))
			|| (!ft_issep(input) && !ft_isquote(*input)))
			input = lex_word(shell, toks, &buf, input);
		else if (ft_issep(input))
			input = lex_sep(shell, toks, &buf, input);
		else
		{
			input = lex_quote(shell, &buf, input, &quote);
			if (!input && scan_ps2_closure(shell, raw, quote))
				return (shell->lines = lineno, vec_free(toks), free(buf),
					lex_prompt(shell, toks, raw, *raw));
		}
		if (!input)
			return (free(buf), vec_free(toks), FALSE);
	}
	return (lex_tok(toks, &buf, NULL));
}

char	*lex_heredoc(t_vec *toks, char *input)
{
	char	*tok;
	char	quote;

	tok = NULL;
	input = ft_strskip(input, ft_isspace, FALSE);
	while (*input && !ft_issep(input))
	{
		if (ft_isquote(*input))
			input = lex_quote(NULL, &tok, input, &quote);
		else
			input = lex_char(&tok, input);
		if (!input)
			return (free(tok), NULL);
	}
	lex_tok(toks, &tok, NULL);
	return (input);
}

char	*lex_sep(t_shell *shell, t_vec *toks, char **buf, char *input)
{
	const char	*op;
	char		*tok;
	t_idx		i;

	if (ft_isspace(*input))
		return (lex_space(shell, toks, buf, input));
	(lex_tok(toks, buf, NULL), i = 0);
	while (ft_isdigit(input[i]))
		i++;
	if (i > 0 && (input[i] == '>' || input[i] == '<'))
	{
		tok = ft_substr(input, 0, i + 1 + (input[i + 1] == input[i]));
		lex_tok(toks, &tok, NULL);
		return (input + i + 1 + (input[i + 1] == input[i]));
	}
	op = get_op(input, DOUBLE);
	if (!op)
		op = get_op(input, SINGLE);
	if (!ft_strcmp(op, "(") && *(input + 1) == '(' && !shell->paren)
		shell->paren = shell->lines;
	tok = ft_strdup(op);
	(lex_tok(toks, &tok, NULL), input += ft_strlen(op));
	if (!ft_strcmp(op, "<<"))
		return (lex_heredoc(toks, input));
	return (input);
}

char	*lex_quote(t_shell *shell, char **buf, char *input, char *quote)
{
	char	*tok;
	size_t	len;

	(void)((shell && !shell->quote) && (shell->quote = shell->lines));
	*quote = *input;
	input = lex_char(buf, input);
	while (input && *input && *input != *quote)
	{
		if (*input == '\n' && shell)
			shell->lines++;
		if (*quote == '"' && *input == '$')
		{
			len = (size_t)(ft_strskip(input + 1, ft_isalnumbar, FALSE) - input);
			if (*(input + 1) == '?')
				len = 2;
			tok = cast_env(shell, ft_substr(input, 0, len));
			(ft_stradd(buf, tok), free(tok), input += len);
		}
		else
			input = lex_char(buf, input);
	}
	if (!input || !*input)
		return (NULL);
	(void)(shell && (shell->quote = 0));
	return (lex_char(buf, input));
}

char	*lex_word(t_shell *shell, t_vec *toks, char **buf, char *input)
{
	char	*tok;
	size_t	len;

	if (*input == '$')
	{
		len = ft_strskip(input + 1, ft_isalnumbar, FALSE) - input;
		if (*(input + 1) == '?')
			len = 2;
		tok = ft_substr(input, 0, len);
		tok = cast_env(shell, tok);
		if (!tok || !*tok)
		{
			(lex_tok(toks, buf, NULL), free(tok));
			tok = ft_substr(input, 0, len);
			lex_tok(toks, &tok, ft_strdup(""));
			return (len + input);
		}
		if (!lex_env(toks, buf, tok))
			return (free(tok), NULL);
		return (free(tok), len + input);
	}
	return (lex_char(buf, input));
}
