/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_run.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ucho <ucho@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 12:31:16 by ucho              #+#    #+#             */
/*   Updated: 2026/01/29 04:25:12 by ucho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	put_intro(void);

int	run_shell(t_shell *shell, t_lexer *lexer)
{
	t_tok	*tok;

	if (get_shellmode(READ) && isatty(STDOUT))
		put_intro();
	while (!reset_shell(shell, lexer, &shell->root))
	{
		if (get_signal(shell), !scan_ps1(shell, lexer))
			continue ;
		shell->root = parse_prompt(shell, lexer);
		if (!shell->root)
		{
			if (!get_shellmode(READ))
				exit(shell->code);
			continue ;
		}
		if (lexer->cur != lexer->toks.len)
		{
			tok = (t_tok *)vec_at(&lexer->toks, lexer->cur);
			if (put_tokerr(shell, tok->val, FALSE), !get_shellmode(READ))
				exit(shell->code);
			continue ;
		}
		shell->code = exec_shell(shell, shell->root);
	}
	return (shell->code);
}

int	exec_shell(t_shell *shell, t_node *node)
{
	if (!node)
		return (FALSE);
	if (node->kind == K_PROMPT)
		return (exec_prompt(shell, (t_prompt *)node->data));
	else if (node->kind == K_PIPELINE)
		return (exec_pipeline(shell, (t_pipeline *)node->data));
	else if (node->kind == K_SUBSHELL)
		return (exec_subshell(shell, (t_subshell *)node->data));
	else if (node->kind == K_CMDLINE)
		return (exec_cmdline(shell, (t_cmdline *)node->data));
	return (TRUE);
}

void	*reset_shell(t_shell *shell, t_lexer *lexer, t_node **node)
{
	if (node && *node)
	{
		if ((*node)->kind == K_PROMPT)
			reset_prompt((t_prompt *)(*node)->data);
		else if ((*node)->kind == K_CMDLINE)
			reset_cmdline((t_cmdline *)(*node)->data);
		else if ((*node)->kind == K_PIPELINE)
			reset_pipeline((t_pipeline *)(*node)->data);
		else if ((*node)->kind == K_SUBSHELL)
			reset_subshell((t_subshell *)(*node)->data);
		free(*node);
		*node = NULL;
	}
	if (lexer && shell)
	{
		vec_free(&lexer->toks);
		lexer->cur = 0;
		shell->quote = 0;
		shell->paren = 0;
	}
	return (NULL);
}
