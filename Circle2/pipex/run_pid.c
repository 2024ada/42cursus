/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_pid.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ucho <ucho@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 02:33:38 by ada               #+#    #+#             */
/*   Updated: 2025/07/31 00:57:34 by ucho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	let_exec(char **cmds, t_info *info, int code)
{
	let_strs(cmds);
	free(info->pid);
	exit(code);
}

void	run_exec(char *arg, t_info *info)
{
	char	**cmds;
	char	*cmd;

	cmds = cut_cmd(arg, ' ');
	if (!cmds || !cmds[0])
		let_exec(cmds, info, 127);
	cmd = get_cmd(cmds[0], info->envp);
	if (!cmd)
	{
		if (access(cmds[0], F_OK) == 0 && access(cmds[0], X_OK) != 0)
		{
			put_info(info->argv[0]);
			perror(cmds[0]);
			let_exec(cmds, info, 126);
		}
		ft_putstr_fd(cmds[0], 2);
		ft_putstr_fd(": command not found\n", 2);
		let_exec(cmds, info, 127);
	}
	execve(cmd, cmds, info->envp);
	perror(cmd);
	free(cmd);
	if (errno == EACCES)
		let_exec(cmds, info, 126);
	let_exec(cmds, info, 127);
}

int	set_exec(int in_fd, int out_fd)
{
	dup2(in_fd, STDIN_FILENO);
	dup2(out_fd, STDOUT_FILENO);
	if (in_fd != STDIN_FILENO)
		close(in_fd);
	if (out_fd != STDOUT_FILENO)
		close(out_fd);
	return (1);
}

void	set_proc(t_info *info, int *files, int *prev_fd, int i)
{
	int	pipe_fd[2];

	if ((info->in == 1 && i == 0)
		|| (info->out == 1 && i == info->size - 1))
		return ;
	if (i < info->size - 1 && pipe(pipe_fd) < 0)
		perror("pipe");
	info->pid[i] = fork();
	if (info->pid[i] < 0)
		perror("fork");
	if (info->pid[i] == 0)
	{
		if (i < info->size - 1)
			(close(pipe_fd[0]), set_exec(*prev_fd, pipe_fd[1]));
		else
			set_exec(*prev_fd, files[1]);
		run_exec(info->argv[2 + i + info->here_doc], info);
	}
	close(*prev_fd);
	if (i < info->size - 1)
	{
		close(pipe_fd[1]);
		*prev_fd = pipe_fd[0];
	}
}

int	run_pid(t_info *info, int files[2])
{
	int		prev_fd;
	int		i;
	int		status;
	int		last_status;

	prev_fd = files[0];
	i = 0;
	while (i < info->size)
		set_proc(info, files, &prev_fd, i++);
	i = 0;
	last_status = 0;
	while (i < info->size)
	{
		if (info->pid[i] > 0)
		{
			waitpid(info->pid[i], &status, 0);
			if (info->pid[i] == info->pid[info->size - 1])
				last_status = status;
		}
		i++;
	}
	if (WIFEXITED(last_status))
		return (WEXITSTATUS(last_status));
	return (1);
}
