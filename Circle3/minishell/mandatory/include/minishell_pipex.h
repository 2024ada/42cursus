/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_pipex.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ucho <ucho@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 00:00:00 by ucho              #+#    #+#             */
/*   Updated: 2026/01/29 04:27:22 by ucho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_PIPEX_H
# define MINISHELL_PIPEX_H

# include "minishell_parse.h"
# include <sys/types.h>

int		pipex(t_shell *shell, t_vec *cmdlines);
void	run_pipex(t_shell *shell, t_vec *cmdlines, pid_t *pids);
int		reset_pipex(t_shell *shell, t_vec *cmdlines, pid_t *pids, int *stats);

int		run_builtin_parent(t_shell *shell, char **cmdp);
void	run_builtin_child(t_shell *shell, char **cmd);
void	run_external(t_shell *shell, char **cmd);

#endif
