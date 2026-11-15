/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_parse.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ucho <ucho@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 00:00:00 by ucho              #+#    #+#             */
/*   Updated: 2026/01/29 04:27:23 by ucho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_PARSE_H
# define MINISHELL_PARSE_H

# include "minishell_vector.h"
# include "minishell_lex.h"

typedef struct s_shell	t_shell;

typedef enum e_kind
{
	K_PROMPT,
	K_PIPELINE,
	K_SUBSHELL,
	K_CMDLINE
}	t_kind;

typedef struct s_node
{
	t_kind	kind;
	void	*data;
}	t_node;

typedef struct s_redir
{
	int		quote;
	int		fd;
	char	*op;
	t_tok	tg;
}	t_redir;

typedef struct s_cmdline
{
	char	*exe;
	t_vec	args;
	t_vec	redirs;
}	t_cmdline;

typedef struct s_pipeline
{
	t_vec	cmdlines;
}	t_pipeline;

typedef struct s_prompt
{
	t_vec	pipelines;
	t_vec	ops;
}	t_prompt;

typedef struct s_subshell
{
	void	*prompt;
	t_vec	redirs;
}	t_subshell;

t_node	*new_prompt(void);
t_node	*new_pipeline(void);
t_node	*new_cmdline(void);
t_node	*new_subshell(void *prompt);

t_node	*parse_prompt(t_shell *shell, t_lexer *lexer);
t_node	*parse_pipeline(t_shell *shell, t_lexer *lexer);
t_node	*parse_cmdline(t_shell *shell, t_lexer *lexer);
t_node	*parse_subshell(t_shell *shell, t_lexer *lexer);

int		parse_exe(t_cmdline *cmdline, char *tok);
int		parse_arg(t_vec *args, char *tok);
int		parse_redirs(t_shell *shell, t_lexer *lexer, t_vec *redirs);
char	*parse_target(const char *tok, int *has_quote, int *status);
int		parse_heredoc(t_shell *shell, t_redir *redir);

void	free_pipeline(void *elem);
void	free_cmdline(void *elem);
void	free_redir(void *elem);

void	reset_prompt(t_prompt *prompt);
void	reset_pipeline(t_pipeline *pipeline);
void	reset_cmdline(t_cmdline *cmdline);
void	reset_subshell(t_subshell *subshell);
void	reset_heredoc(char *target);

#endif
