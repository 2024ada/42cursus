/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_execute_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ucho <ucho@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 12:31:16 by ucho              #+#    #+#             */
/*   Updated: 2026/01/29 04:23:23 by ucho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

void	set_redirs(t_shell *shell, t_vec *redirs);

int	exec_prompt(t_shell *shell, t_prompt *prompt)
{
	t_pipeline	*pipeline;
	char		*op;
	t_idx		i;

	i = -1;
	while (++i < prompt->pipelines.len)
	{
		pipeline = (t_pipeline *)vec_at(&prompt->pipelines, i);
		if (i > 0)
		{
			op = vec_to_str(&prompt->ops, i - 1, 0, TRUE);
			if (ft_strcmp(op, "&&") == 0 && shell->code != 0)
				continue ;
			else if (ft_strcmp(op, "||") == 0 && shell->code == 0)
				continue ;
		}
		if (pipeline)
			shell->code = exec_pipeline(shell, pipeline);
	}
	return (shell->code);
}

static int	set_pipeline(t_shell *shell, t_pipeline *pipeline)
{
	t_node		*node;
	t_cmdline	*cmdline;
	char		**cmdp;
	int			code;
	t_idx		i;

	i = -1;
	while (++i < pipeline->cmdlines.len)
	{
		node = *(t_node **)vec_at(&pipeline->cmdlines, i);
		if (node && node->kind == K_CMDLINE)
		{
			cmdline = (t_cmdline *)node->data;
			if (pipeline->cmdlines.len == 1)
			{
				cmdp = cmdline_to_cmdp(cmdline);
				code = run_builtin_parent(shell, cmdp);
				if (code != NONE)
					return (code);
			}
		}
	}
	return (NONE);
}

int	exec_pipeline(t_shell *shell, t_pipeline *pipeline)
{
	pid_t	pid;
	int		stat;

	stat = set_pipeline(shell, pipeline);
	if (stat != NONE)
		return (stat);
	set_signal(SIG_IGN, 0, SIGINT);
	pid = fork();
	if (pid < 0)
	{
		set_signal(default_handler, 0, SIGINT);
		return (perror(SHELL": fork"), FAILURE);
	}
	if (pid == 0)
	{
		set_signal(default_handler, 0, SIGINT);
		exit(pipex(shell, &pipeline->cmdlines));
	}
	waitpid(pid, &stat, 0);
	set_signal(default_handler, 0, SIGINT);
	if (WIFEXITED(stat))
		return (WEXITSTATUS(stat));
	else if (WIFSIGNALED(stat))
		return (128 + WTERMSIG(stat));
	return (FAILURE);
}

int	exec_cmdline(t_shell *shell, t_cmdline *cmdline)
{
	t_pipeline	pipeline;
	t_node		*node_ptr;

	node_ptr = &(t_node){.kind = K_CMDLINE, .data = cmdline};
	ft_memset(&pipeline, 0, sizeof(t_pipeline));
	pipeline.cmdlines.len = 1;
	pipeline.cmdlines.cap = 1;
	pipeline.cmdlines.size = sizeof(void *);
	pipeline.cmdlines.data = &node_ptr;
	pipeline.cmdlines.free = NULL;
	return (exec_pipeline(shell, &pipeline));
}

int	exec_subshell(t_shell *shell, t_subshell *subshell)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid < 0)
		return (perror(SHELL": fork"), FAILURE);
	if (pid == 0)
	{
		set_redirs(shell, &subshell->redirs);
		status = exec_shell(shell, (t_node *)subshell->prompt);
		exit(status);
	}
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	else if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
	return (FAILURE);
}
