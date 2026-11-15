/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ucho <ucho@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 04:12:15 by ucho              #+#    #+#             */
/*   Updated: 2025/05/27 15:12:27 by ucho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	pipex(t_info *info)
{
	int	files[2];
	int	exit_code_cmds;

	set_file(info, files);
	set_pid(info);
	exit_code_cmds = run_pid(info, files);
	if (info->pid)
	{
		free(info->pid);
		info->pid = NULL;
	}
	if (info->here_doc)
		get_next_line(-42);
	if (info->out)
		exit(1);
	else
		exit(exit_code_cmds);
}

int	main(int argc, char **argv, char **envp)
{
	t_info	info;

	if (argc < 2)
		return (1);
	info.argc = argc;
	info.argv = argv;
	info.envp = envp;
	info.pid = NULL;
	info.in = 0;
	info.out = 0;
	pipex(&info);
	return (0);
}
