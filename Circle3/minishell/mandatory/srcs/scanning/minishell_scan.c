/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_scan.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ucho <ucho@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 13:01:02 by ucho              #+#    #+#             */
/*   Updated: 2026/01/29 04:24:49 by ucho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	scan_ps2_continue(t_shell *shell, t_vec *toks);

int	scan_prompt(t_shell *shell, t_lexer *lexer)
{
	t_vec	toks;
	t_tok	*tok;
	t_idx	i;

	while (lexer->cur >= lexer->toks.len)
	{
		if (!scan_ps2_continue(shell, &toks))
			return (FALSE);
		i = 0;
		while (i < toks.len)
		{
			tok = (t_tok *)vec_at(&toks, i);
			vec_push(&lexer->toks, tok);
			i++;
		}
		toks.free = NULL;
		vec_free(&toks);
	}
	return (TRUE);
}

static int	scan_ps2_continue(t_shell *shell, t_vec *toks)
{
	char	*raw;

	if (get_signal(shell))
		return (reset_multiline(shell), FALSE);
	raw = get_readline(shell, "> ", TRUE);
	if (get_signal(shell))
		return (reset_multiline(shell), FALSE);
	if (!raw)
	{
		if (shell->paren)
			put_tokerr(shell, ")", TRUE);
		else
		{
			put_syntaxerr(shell, TRUE);
			if (get_shellmode(READ))
				ft_putendl_fd("exit", STDOUT);
			exit(2);
		}
		return (FALSE);
	}
	shell->lines++;
	(free(shell->input), shell->input = ft_strdup(raw));
	if (!lex_prompt(shell, toks, &raw, raw))
		return (get_signal(shell), free(raw), FALSE);
	return (free(raw), TRUE);
}

int	scan_ps2_closure(t_shell *shell, char **input, char quote)
{
	char	*raw;
	char	*tmp;

	if (get_signal(shell))
		return (FALSE);
	raw = get_readline(shell, "> ", TRUE);
	if (get_signal(shell))
		return (free(raw), FALSE);
	if (!raw)
		return (put_tokerr(shell, (char []){quote, 0}, TRUE), FALSE);
	shell->lines++;
	tmp = ft_strsjoin((char *[]){*input, "\n", raw, NULL});
	free(*input);
	*input = tmp;
	free(raw);
	return (TRUE);
}

int	scan_ps1(t_shell *shell, t_lexer *lexer)
{
	char	*raw;

	if (get_signal(shell))
	{
		if (get_shellmode(READ))
			return (FALSE);
		exit(shell->code);
	}
	raw = get_readline(shell, PROMPT, FALSE);
	get_signal(shell);
	if (!raw)
	{
		if (get_shellmode(READ))
			ft_putendl_fd("exit", STDOUT);
		exit(shell->code);
	}
	(set_multiline(shell, raw), shell->lines++);
	(free(shell->input), shell->input = ft_strdup(raw));
	if (!*raw)
		return (free(raw), FALSE);
	if (get_shellmode(READ))
		add_history(raw);
	if (!lex_prompt(shell, &lexer->toks, &raw, raw))
		return (get_signal(shell), free(raw), FALSE);
	return (free(raw), TRUE);
}
