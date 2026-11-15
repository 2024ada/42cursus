/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_pwd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ucho <ucho@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 12:45:10 by ucho              #+#    #+#             */
/*   Updated: 2026/01/29 04:27:03 by ucho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_pwd(t_shell *shell)
{
	char	*cwd;
	char	*pwd_env;

	cwd = getcwd(NULL, 0);
	if (cwd == NULL)
	{
		pwd_env = get_enval(shell->envs, "PWD");
		if (pwd_env)
		{
			ft_putendl_fd(pwd_env, STDOUT);
			return (SUCCESS);
		}
		perror("getcwd");
		return (FAILURE);
	}
	ft_putendl_fd(cwd, STDOUT);
	free(cwd);
	return (SUCCESS);
}
