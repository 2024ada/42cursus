/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ucho <ucho@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 21:52:19 by ucho              #+#    #+#             */
/*   Updated: 2025/05/27 15:12:40 by ucho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libft/libft.h"
# include "get_next_line/get_next_line.h"
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <errno.h>

typedef struct s_info
{
	int		argc;
	char	**argv;
	char	**envp;
	int		size;
	pid_t	*pid;
	int		in;
	int		out;
	int		here_doc;
}	t_info;

void	put_info(char *program);
void	let_strs(char **dirs);
int		get_tockenlen(const char *s, int *i, char delim);
char	*get_str(char *str, int start, int len);
char	**get_strs(char **strs, char *str, char charset, int count);
char	**set_strs(char *str, char charset, int count);
char	**cut_cmd(const char *s, char c);
char	*get_path(char **envp);
char	*get_exec(char *dir, const char *cmd);
char	*get_cmd(const char *cmd, char **envp);
void	set_infile(t_info *info, int *files);
void	set_outfile(t_info *info, int *files);
void	set_file(t_info *info, int files[2]);
void	set_pid(t_info *info);
void	let_exec(char **cmds, t_info *info, int code);
void	run_exec(char *arg, t_info *info);
int		set_exec(int in_fd, int out_fd);
void	set_proc(t_info *info, int *files, int *prev_fd, int i);
int		run_pid(t_info *info, int files[2]);
void	pipex(t_info *info);

#endif
