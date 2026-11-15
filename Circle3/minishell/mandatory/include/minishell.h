/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ucho <ucho@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 10:00:00 by ucho              #+#    #+#             */
/*   Updated: 2026/01/29 04:27:14 by ucho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define _GNU_SOURCE

# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <dirent.h>
# include <stdio.h>
# include <signal.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <errno.h>
# include <termios.h>

# include "minishell_libft.h"

# include "minishell_vector.h"

# include "minishell_signal.h"

# include "minishell_scan.h"
# include "minishell_lex.h"
# include "minishell_parse.h"
# include "minishell_execute.h"

# include "minishell_pipex.h"
# include "minishell_builtin.h"

# include "minishell_env.h"
# include "minishell_wildcard.h"

# include "minishell_convert.h"
# include "minishell_utils.h"

# define TRUE 1
# define FALSE 0

# define NONE -1

# define SUCCESS 0
# define FAILURE 1
# define MISUSE 2

# define STDIN 0
# define STDOUT 1
# define STDERR 2

# define DOUBLE 0
# define SINGLE 1
# define READ -1
# define SHELL "mini"
# define PROMPT "\001\033[2K\r\033[1;38;2;204;135;94m\002🍫 mini\001\033[0m\002$ "
# define HEREDOC_DIR "/tmp/.mini_heredoc"

# define INT_MAX 2147483647
# define INT_MIN -2147483648

typedef struct s_shell
{
	t_node	*root;
	t_vec	*envs;
	char	*input;
	int		fd;
	size_t	lines;
	size_t	quote;
	size_t	paren;
	size_t	heredoc;
	size_t	code;
}	t_shell;

int			get_shellmode(int is_tty);

void		set_shell(t_shell *shell, t_lexer *lexer, char *argv, char **envp);
int			run_shell(t_shell *shell, t_lexer *lexer);
int			exec_shell(t_shell *shell, t_node *node);
void		*reset_shell(t_shell *shell, t_lexer *lexer, t_node **node);

#endif
