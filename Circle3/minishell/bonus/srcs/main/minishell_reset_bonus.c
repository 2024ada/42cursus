/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_reset_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ucho <ucho@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 13:04:38 by ucho              #+#    #+#             */
/*   Updated: 2026/01/29 04:21:10 by ucho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

void	reset_prompt(t_prompt *prompt)
{
	if (!prompt)
		return ;
	vec_free(&prompt->pipelines);
	vec_free(&prompt->ops);
	free(prompt);
}

void	reset_cmdline(t_cmdline *cmdline)
{
	if (!cmdline)
		return ;
	free(cmdline->exe);
	vec_free(&cmdline->args);
	vec_free(&cmdline->redirs);
	free(cmdline);
}

void	reset_subshell(t_subshell *subshell)
{
	if (!subshell)
		return ;
	reset_shell(NULL, NULL, (t_node **)&subshell->prompt);
	vec_free(&subshell->redirs);
	free(subshell);
}

void	reset_pipeline(t_pipeline *pipeline)
{
	if (!pipeline)
		return ;
	vec_free(&pipeline->cmdlines);
	free(pipeline);
}

void	reset_heredoc(char *target)
{
	if (target && !ft_strncmp(target, HEREDOC_DIR, ft_strlen(HEREDOC_DIR)))
		unlink(target);
}
