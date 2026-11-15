/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_parse_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ucho <ucho@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 00:41:34 by ucho              #+#    #+#             */
/*   Updated: 2026/01/29 04:25:04 by ucho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_pipeline(void *elem)
{
	t_pipeline	*pipeline;

	pipeline = (t_pipeline *)elem;
	if (!pipeline)
		return ;
	vec_free(&pipeline->cmdlines);
}

void	free_cmdline(void *elem)
{
	t_node	**node;

	node = (t_node **)elem;
	if (node && *node)
		reset_shell(NULL, NULL, node);
}

void	free_redir(void *elem)
{
	t_redir	*redir;

	redir = (t_redir *)elem;
	if (redir)
	{
		if (redir->op && ft_strcmp(redir->op, "<<") == 0)
			reset_heredoc(redir->tg.val);
		free(redir->op);
		free_tok(&redir->tg);
	}
}
