/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_scan.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ucho <ucho@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 00:00:00 by ucho              #+#    #+#             */
/*   Updated: 2026/01/29 04:27:20 by ucho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_SCAN_H
# define MINISHELL_SCAN_H

# include "minishell_lex.h"

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1000
# endif

typedef struct s_buf
{
	int				fd;
	char			*buf;
	struct s_buf	*next;
}	t_buf;

int		scan_prompt(t_shell *shell, t_lexer *lexer);
int		scan_ps1(t_shell *shell, t_lexer *lexer);
int		scan_ps2_closure(t_shell *shell, char **input, char quote);

char	*get_nextline(int fd);
char	*get_readline(t_shell *shell, const char *prompt, int is_ps2);

int		set_multiline(t_shell *shell, char *raw);
void	reset_multiline(t_shell *shell);

#endif
