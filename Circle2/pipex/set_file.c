/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_file.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ucho <ucho@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 02:32:47 by ada               #+#    #+#             */
/*   Updated: 2025/05/27 18:37:51 by ucho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	set_infile(t_info *info, int *files)
{
	info->here_doc = 0;
	files[0] = open(info->argv[1], O_RDONLY);
	if (files[0] < 0)
	{
		put_info(info->argv[0]);
		if (info->argv[1][0] == '\0')
			ft_putstr_fd(": ", 2);
		perror(info->argv[1]);
		info->in = 1;
		files[0] = open("/dev/null", O_RDONLY);
		if (info->argc == 2)
			exit(1);
	}
}

void	set_outfile(t_info *info, int *files)
{
	if (info->here_doc)
		files[1] = open(info->argv[info->argc - 1],
				O_CREAT | O_WRONLY | O_APPEND, 0644);
	else
		files[1] = open(info->argv[info->argc - 1],
				O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (files[1] < 0)
	{
		put_info(info->argv[0]);
		if (info->argv[info->argc - 1][0] == '\0')
			ft_putstr_fd(": ", 2);
		perror(info->argv[info->argc - 1]);
		info->out = 1;
		files[1] = open("/dev/null", O_WRONLY);
		if (files[1] < 0)
		{
			perror("/dev/null");
			exit(EXIT_FAILURE);
		}
	}
}

void	set_heredoc(t_info *info, int files[2])
{
	int		hd_pipe[2];
	char	*line;

	info->here_doc = 1;
	if (pipe(hd_pipe) < 0)
	{
		perror("pipe");
		exit(EXIT_FAILURE);
	}
	line = get_next_line(STDIN_FILENO);
	while (line)
	{
		if (!ft_strncmp(line, info->argv[2], ft_strlen(info->argv[2]))
			&& (line[ft_strlen(info->argv[2])] == '\n'
				|| line[ft_strlen(info->argv[2])] == '\0'))
		{
			free(line);
			break ;
		}
		write(hd_pipe[1], line, ft_strlen(line));
		free(line);
		line = get_next_line(STDIN_FILENO);
	}
	close(hd_pipe[1]);
	files[0] = hd_pipe[0];
}

void	set_file(t_info *info, int files[2])
{
	char	**cmds;
	char	*cmd;

	if (ft_strncmp(info->argv[1], "here_doc", 8) == 0
		&& ft_strlen(info->argv[1]) == 8)
		set_heredoc(info, files);
	else
		set_infile(info, files);
	info->size = info->argc - (info->here_doc + 2);
	files[1] = STDOUT_FILENO;
	cmds = cut_cmd(info->argv[info->argc - 1], ' ');
	if (!cmds)
		exit(EXIT_FAILURE);
	cmd = get_cmd(cmds[0], info->envp);
	if (!cmd && info->argc > 4 + info->here_doc)
	{
		info->size--;
		set_outfile(info, files);
	}
	if (cmd)
		free(cmd);
	let_strs(cmds);
	if (info->size == 0)
		exit(0);
}
