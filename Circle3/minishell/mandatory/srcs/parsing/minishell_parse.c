/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_parse.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ucho <ucho@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 12:31:16 by ucho              #+#    #+#             */
/*   Updated: 2026/01/29 04:25:03 by ucho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_node	*parse_cmd(t_shell *shell, t_lexer *lexer);

t_node	*parse_prompt(t_shell *shell, t_lexer *lexer)
{
	t_node		*root;
	t_node		*leaf;
	t_prompt	*prompt;
	t_tok		*tok;
	char		*op;

	root = new_prompt();
	prompt = (t_prompt *)root->data;
	while (lexer->cur < lexer->toks.len)
	{
		leaf = parse_pipeline(shell, lexer);
		if (!leaf)
			return (reset_shell(NULL, NULL, &root));
		vec_push(&prompt->pipelines, (t_pipeline *)leaf->data);
		if (free(leaf->data), free(leaf), lexer->cur >= lexer->toks.len)
			break ;
		tok = (t_tok *)vec_at(&lexer->toks, lexer->cur);
		if (!ft_isboolop(tok->val))
			break ;
		op = ft_strdup(tok->val);
		vec_push(&prompt->ops, &op);
		if (lexer->cur++, !scan_prompt(shell, lexer))
			return (reset_shell(NULL, NULL, &root));
	}
	return (root);
}

t_node	*parse_pipeline(t_shell *shell, t_lexer *lexer)
{
	t_node		*root;
	t_node		*leaf;
	t_pipeline	*pipeline;
	t_tok		*tok;

	root = new_pipeline();
	pipeline = (t_pipeline *)root->data;
	while (lexer->cur < lexer->toks.len)
	{
		leaf = parse_cmdline(shell, lexer);
		if (!leaf)
			return (reset_shell(NULL, NULL, &root));
		vec_push(&pipeline->cmdlines, (void **)&leaf);
		if (lexer->cur >= lexer->toks.len)
			break ;
		tok = (t_tok *)vec_at(&lexer->toks, lexer->cur);
		if (!ft_ispipe(tok->val))
			break ;
		lexer->cur++;
		if (!scan_prompt(shell, lexer))
			return (reset_shell(NULL, NULL, &root));
	}
	return (root);
}

t_node	*parse_cmdline(t_shell *shell, t_lexer *lexer)
{
	t_node		*root;
	t_cmdline	*cmdline;
	char		*val;

	val = ((t_tok *)vec_at(&lexer->toks, lexer->cur))->val;
	if (!ft_strncmp(val, "(", 1))
		return (parse_subshell(shell, lexer));
	root = parse_cmd(shell, lexer);
	if (!root)
		return (NULL);
	cmdline = (t_cmdline *)root->data;
	if (lexer->cur >= lexer->toks.len)
		return (root);
	val = ((t_tok *)vec_at(&lexer->toks, lexer->cur))->val;
	if (cmdline->exe && !ft_strncmp(val, "(", 1))
	{
		if (++lexer->cur >= lexer->toks.len)
			return (put_tokerr(shell, "newline", FALSE),
				reset_shell(NULL, NULL, &root));
		val = ((t_tok *)vec_at(&lexer->toks, lexer->cur))->val;
		return (put_tokerr(shell, val, FALSE), reset_shell(NULL, NULL, &root));
	}
	if (!cmdline->exe && !cmdline->redirs.len)
		return (put_tokerr(shell, val, FALSE), reset_shell(NULL, NULL, &root));
	return (root);
}

static t_node	*parse_cmd(t_shell *shell, t_lexer *lexer)
{
	t_node		*root;
	t_cmdline	*cmdline;
	t_tok		*tok;

	root = new_cmdline();
	cmdline = (t_cmdline *)root->data;
	while (lexer->cur < lexer->toks.len)
	{
		tok = (t_tok *)vec_at(&lexer->toks, lexer->cur);
		if (ft_isctrlop(tok->val))
			break ;
		if (ft_isredir(tok->val))
		{
			if (!parse_redirs(shell, lexer, &cmdline->redirs))
				return (reset_shell(NULL, NULL, &root));
		}
		else
		{
			if (!tok->var || *tok->var)
				parse_exe(cmdline, tok->val);
			lexer->cur++;
		}
	}
	return (root);
}

t_node	*parse_subshell(t_shell *shell, t_lexer *lexer)
{
	t_node		*root;
	t_node		*leaf;
	t_tok		*tok;

	lexer->cur++;
	if (!scan_prompt(shell, lexer))
		return (NULL);
	leaf = parse_prompt(shell, lexer);
	if (!leaf)
		return (NULL);
	if (!scan_prompt(shell, lexer))
		return (reset_shell(NULL, NULL, &leaf));
	tok = (t_tok *)vec_at(&lexer->toks, lexer->cur);
	if (ft_strncmp(tok->val, ")", 1) != 0)
	{
		put_tokerr(shell, tok->val, FALSE);
		return (reset_shell(NULL, NULL, &leaf));
	}
	lexer->cur++;
	root = new_subshell(leaf);
	if (!parse_redirs(shell, lexer, &((t_subshell *)root->data)->redirs))
		return (reset_shell(NULL, NULL, &root));
	return (root);
}
