/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ucho <ucho@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 00:00:00 by ucho              #+#    #+#             */
/*   Updated: 2026/01/29 04:27:18 by ucho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_UTILS_H
# define MINISHELL_UTILS_H

# include "minishell_vector.h"

typedef struct s_shell		t_shell;
typedef struct s_prompt		t_prompt;
typedef struct s_pipeline	t_pipeline;
typedef struct s_cmdline	t_cmdline;
typedef struct s_subshell	t_subshell;

int			ft_isspace(char c);
int			ft_isquote(char c);
int			ft_isdollar(char c);
int			ft_isalnumbar(char c);

int			ft_ispipe(const char *str);
int			ft_isboolop(const char *str);
int			ft_isparen(const char *str);
int			ft_isredir(const char *str);

int			ft_isctrlop(const char *str);
int			ft_isop(const char *str);
int			ft_issep(const char *str);

char		*ft_strskip(char *str, int (*f)(char), int invert);
const char	*get_op(const char *str, int op);

void		ft_sort(t_vec *vec, long long offset, int is_ptr);

void		put_tokerr(t_shell *shell, const char *tok, int is_eof);
void		put_syntaxerr(t_shell *shell, int is_eof);
void		put_execerr(t_shell *shell, const char **msg, int is_cmd);
void		put_warning(t_shell *shell, char *delim);

void		free_env(void *elem);
void		free_tok(void *elem);
void		free_str(void *elem);
void		free_strs(char **segs);

#endif
