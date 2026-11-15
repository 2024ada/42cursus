/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_lex_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ucho <ucho@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 00:00:00 by ucho              #+#    #+#             */
/*   Updated: 2026/01/29 04:24:05 by ucho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_LEX_BONUS_H
# define MINISHELL_LEX_BONUS_H

# include "minishell_vector_bonus.h"

typedef struct s_shell			t_shell;

typedef struct s_tok
{
	char	*val;
	char	*var;
	int		err;
}	t_tok;

typedef struct s_lexer
{
	t_vec	toks;
	t_idx	cur;
	int		err;
}	t_lexer;

int		lex_prompt(t_shell *shell, t_vec *toks, char **buf, char *input);
char	*lex_space(t_shell *shell, t_vec *toks, char **buf, char *input);
char	*lex_sep(t_shell *shell, t_vec *toks, char **buf, char *input);
char	*lex_quote(t_shell *shell, char **buf, char *input, char *quote);
char	*lex_word(t_shell *shell, t_vec *toks, char **buf, char *input);
char	*lex_char(char **buf, char *input);
char	*lex_heredoc(t_vec *toks, char *input);

int		lex_tok(t_vec *toks, char **val, char *var);
int		lex_env(t_vec *toks, char **buf, char *var);

#endif
