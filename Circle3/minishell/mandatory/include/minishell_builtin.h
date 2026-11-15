/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_builtin.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ucho <ucho@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 00:00:00 by ucho              #+#    #+#             */
/*   Updated: 2026/01/29 04:27:32 by ucho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_BUILTIN_H
# define MINISHELL_BUILTIN_H

typedef struct s_shell	t_shell;

int	ft_echo(char **str);
int	ft_cd(t_shell *shell, char **str);
int	ft_pwd(t_shell *shell);
int	ft_export(t_shell *shell, char **str);
int	ft_unset(t_shell *shell, char **str);
int	ft_env(t_shell *shell, char **str);
int	ft_exit(t_shell *shell, char **str, int is_called);

#endif
