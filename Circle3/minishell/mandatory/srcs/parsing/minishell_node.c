/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_node.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ucho <ucho@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 13:02:31 by ucho              #+#    #+#             */
/*   Updated: 2026/01/29 04:25:07 by ucho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_node	*new_prompt(void)
{
	t_prompt	*prompt;
	t_node		*node;

	prompt = (t_prompt *)ft_xmalloc(sizeof(t_prompt));
	vec_init(&prompt->pipelines, sizeof(t_pipeline), 4, free_pipeline);
	vec_init(&prompt->ops, sizeof(void *), 2, free_str);
	node = (t_node *)ft_xmalloc(sizeof(t_node));
	node->kind = K_PROMPT;
	node->data = prompt;
	return (node);
}

t_node	*new_pipeline(void)
{
	t_pipeline	*pipeline;
	t_node		*node;

	pipeline = (t_pipeline *)ft_xmalloc(sizeof(t_pipeline));
	vec_init(&pipeline->cmdlines, sizeof(void *), 4, free_cmdline);
	node = (t_node *)ft_xmalloc(sizeof(t_node));
	node->kind = K_PIPELINE;
	node->data = pipeline;
	return (node);
}

t_node	*new_cmdline(void)
{
	t_cmdline	*cmdline;
	t_node		*node;

	cmdline = (t_cmdline *)ft_xmalloc(sizeof(t_cmdline));
	cmdline->exe = NULL;
	vec_init(&cmdline->args, sizeof(char *), 4, free_str);
	vec_init(&cmdline->redirs, sizeof(t_redir), 2, free_redir);
	node = (t_node *)ft_xmalloc(sizeof(t_node));
	node->kind = K_CMDLINE;
	node->data = cmdline;
	return (node);
}

t_node	*new_subshell(void *prompt)
{
	t_subshell	*subshell;
	t_node		*node;

	subshell = (t_subshell *)ft_xmalloc(sizeof(t_subshell));
	subshell->prompt = prompt;
	vec_init(&subshell->redirs, sizeof(t_redir), 2, free_redir);
	node = (t_node *)ft_xmalloc(sizeof(t_node));
	node->kind = K_SUBSHELL;
	node->data = subshell;
	return (node);
}
