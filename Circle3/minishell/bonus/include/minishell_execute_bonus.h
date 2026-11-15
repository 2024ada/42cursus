/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_execute_bonus.h                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ucho <ucho@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 00:00:00 by ucho              #+#    #+#             */
/*   Updated: 2026/01/29 04:24:06 by ucho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_EXECUTE_BONUS_H
# define MINISHELL_EXECUTE_BONUS_H

# include "minishell_parse_bonus.h"

int		exec_prompt(t_shell *shell, t_prompt *prompt);
int		exec_pipeline(t_shell *shell, t_pipeline *pipeline);
int		exec_cmdline(t_shell *shell, t_cmdline *cmdline);
int		exec_subshell(t_shell *shell, t_subshell *subshell);
char	*exec_heredoc(t_shell *shell, t_redir *redir, char *tmpf);

#endif
