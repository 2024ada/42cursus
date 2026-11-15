/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_run_pipex.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ucho <ucho@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 18:22:40 by ucho              #+#    #+#             */
/*   Updated: 2026/01/29 04:26:47 by ucho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		set_redirs(t_shell *shell, t_vec *redirs);
static void	run_cmdline(t_node *node, t_shell *shell, int in, int out);

void	run_pipex(t_shell *shell, t_vec *cmdlines, pid_t *pids)
{
	t_node	*node;
	int		fds[2];
	int		fd;
	t_idx	i;

	fd = STDIN;
	i = -1;
	while (++i < cmdlines->len)
	{
		if (i < cmdlines->len - 1 && pipe(fds) < 0)
			return (perror(SHELL": pipe error"));
		pids[i] = fork();
		if (pids[i] == 0)
		{
			(set_signal(SIG_DFL, 0, SIGINT), set_signal(SIG_DFL, 0, SIGQUIT));
			node = *(t_node **)vec_at(cmdlines, i);
			if (i < cmdlines->len - 1)
				(close(fds[0]), run_cmdline(node, shell, fd, fds[1]));
			else
				run_cmdline(node, shell, fd, STDOUT);
		}
		(void)(fd != STDIN && close(fd));
		if (i < cmdlines->len - 1)
			(close(fds[1]), fd = fds[0]);
	}
}

static int	is_builtin(char *exe)
{
	return (!ft_strcmp(exe, "echo") || !ft_strcmp(exe, "pwd")
		|| !ft_strcmp(exe, "export") || !ft_strcmp(exe, "unset")
		|| !ft_strcmp(exe, "env") || !ft_strcmp(exe, "cd")
		|| !ft_strcmp(exe, "exit"));
}

static void	run_exe(char **cmdp, t_shell *shell)
{
	const char	*texts[] = {cmdp[0], NULL, NULL};

	if (!cmdp || !cmdp[0])
		exit(0);
	if (!cmdp[0][0])
	{
		texts[1] = "command not found";
		put_execerr(shell, texts, !get_shellmode(READ));
		exit(127);
	}
	if (is_builtin(cmdp[0]))
		run_builtin_child(shell, cmdp);
	else
		run_external(shell, cmdp);
}

static void	run_cmdline(t_node *node, t_shell *shell, int in, int out)
{
	t_cmdline	*cmdline;
	t_subshell	*subshell;
	char		**cmdp;

	dup2(in, STDIN);
	dup2(out, STDOUT);
	if (in != STDIN)
		close(in);
	if (out != STDOUT)
		close(out);
	if (node->kind == K_CMDLINE)
	{
		cmdline = (t_cmdline *)node->data;
		set_redirs(shell, &cmdline->redirs);
		cmdp = cmdline_to_cmdp(cmdline);
		run_exe(cmdp, shell);
	}
	else if (node->kind == K_SUBSHELL)
	{
		subshell = (t_subshell *)node->data;
		set_redirs(shell, &subshell->redirs);
		exit(exec_shell(shell, subshell->prompt));
	}
}

char	**cmdline_to_cmdp(t_cmdline *cmdline)
{
	char	**cmdp;
	t_idx	i;

	cmdp = ft_xmalloc(sizeof(char *) * (cmdline->args.len + 2));
	cmdp[0] = cmdline->exe;
	i = -1;
	while (++i < cmdline->args.len)
		cmdp[1 + i] = vec_to_str(&cmdline->args, i, 0, TRUE);
	cmdp[cmdline->args.len + 1] = NULL;
	return (cmdp);
}
