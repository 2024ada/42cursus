/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_builtin_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ucho <ucho@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 18:26:13 by ucho              #+#    #+#             */
/*   Updated: 2026/01/29 04:23:24 by ucho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

int	run_builtin_parent(t_shell *shell, char **cmdp)
{
	char	*exe;
	int		code;

	if (!cmdp || !cmdp[0])
		return (free(cmdp), NONE);
	code = 0;
	exe = cmdp[0];
	if (ft_strcmp(exe, "cd")
		&& ft_strcmp(exe, "export")
		&& ft_strcmp(exe, "unset")
		&& ft_strcmp(exe, "exit"))
		return (free(cmdp), NONE);
	if (!ft_strcmp(exe, "cd"))
		code = ft_cd(shell, cmdp);
	else if (!ft_strcmp(exe, "export"))
		code = ft_export(shell, cmdp);
	else if (!ft_strcmp(exe, "unset"))
		code = ft_unset(shell, cmdp);
	else if (!ft_strcmp(exe, "exit"))
		code = ft_exit(shell, cmdp, TRUE);
	return (free(cmdp), code);
}

void	run_builtin_child(t_shell *shell, char **cmdp)
{
	char	*exe;
	int		code;

	code = 0;
	exe = cmdp[0];
	if (!ft_strcmp(exe, "echo"))
		code = ft_echo(cmdp);
	else if (!ft_strcmp(exe, "cd"))
		code = ft_cd(shell, cmdp);
	else if (!ft_strcmp(exe, "pwd"))
		code = ft_pwd(shell);
	else if (!ft_strcmp(exe, "export"))
		code = ft_export(shell, cmdp);
	else if (!ft_strcmp(exe, "unset"))
		code = ft_unset(shell, cmdp);
	else if (!ft_strcmp(exe, "env"))
		code = ft_env(shell, cmdp);
	else if (!ft_strcmp(exe, "exit"))
		code = ft_exit(shell, cmdp, FALSE);
	free(cmdp);
	exit(code);
}
