/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_cd_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ucho <ucho@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 12:44:23 by ucho              #+#    #+#             */
/*   Updated: 2026/01/29 04:23:46 by ucho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

static char	*get_homedir(t_shell *shell, char **str);
static int	set_pwd(t_shell *shell, char *old, char *target);
static int	put_cwderr(t_shell *shell, char *old, char *target);

int	ft_cd(t_shell *shell, char **str)
{
	char		*target;
	char		*old;
	const char	*texts[] = {"cd", NULL, NULL, NULL};

	if (str[1] && str[2])
	{
		texts[1] = "too many arguments";
		return (put_execerr(shell, texts, TRUE), FAILURE);
	}
	target = get_homedir(shell, str);
	if (!target)
		return (FAILURE);
	old = get_enval(shell->envs, "PWD");
	if (chdir(target) != 0)
	{
		texts[1] = target;
		texts[2] = strerror(errno);
		return (put_execerr(shell, texts, TRUE), FAILURE);
	}
	return (set_pwd(shell, old, target));
}

static char	*get_homedir(t_shell *shell, char **str)
{
	char		*target;
	const char	*texts[] = {"cd", "HOME not set", NULL};

	if (str[1])
		return (str[1]);
	target = get_enval(shell->envs, "HOME");
	if (!target)
	{
		put_execerr(shell, texts, TRUE);
		return (NULL);
	}
	return (target);
}

static int	set_pwd(t_shell *shell, char *old, char *target)
{
	char	*new;

	new = getcwd(NULL, 0);
	if (!new)
		return (put_cwderr(shell, old, target));
	add_env(shell->envs, "OLDPWD", old);
	add_env(shell->envs, "PWD", new);
	free(new);
	return (SUCCESS);
}

static int	put_cwderr(t_shell *shell, char *old, char *target)
{
	char		*new;
	const char	*texts[] = {"cd", "error retrieving current directory",
		"getcwd", "cannot access parent directories", NULL, NULL};

	texts[4] = strerror(errno);
	if (!get_shellmode(READ))
		texts[0] = "chdir";
	put_execerr(shell, texts, FALSE);
	if (old && target)
	{
		add_env(shell->envs, "OLDPWD", old);
		new = ft_strsjoin((char *[]){old, "/", target, NULL});
		add_env(shell->envs, "PWD", new);
		free(new);
	}
	return (SUCCESS);
}
