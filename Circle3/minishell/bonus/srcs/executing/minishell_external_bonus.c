/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_external_bonus.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ucho <ucho@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 12:56:59 by ucho              #+#    #+#             */
/*   Updated: 2026/01/29 04:23:21 by ucho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

static char	*get_relexe(char **cmdp, t_vec *envs, const char **texts,
				t_shell *shell);
static char	*get_absexe(char **cmdp, const char **texts, t_shell *shell);

void	run_external(t_shell *shell, char **cmdp)
{
	char		*exe;
	char		**envp;
	const char	*texts[] = {cmdp[0], NULL, NULL};

	if (ft_strchr(cmdp[0], '/'))
		exe = get_absexe(cmdp, texts, shell);
	else
		exe = get_relexe(cmdp, shell->envs, texts, shell);
	envp = envs_to_envp(shell->envs);
	execve(exe, cmdp, envp);
	texts[0] = exe;
	texts[1] = strerror(errno);
	put_execerr(shell, texts, FALSE);
	free_str(envp);
	free(exe);
	free(cmdp);
	if (errno == EACCES)
		exit(126);
	exit(127);
}

static char	*get_exe(char **dirs, char *cmdp)
{
	char		*exe;
	struct stat	st;
	t_idx		i;

	i = -1;
	while (dirs[++i])
	{
		exe = ft_strsjoin((char *[]){dirs[i], "/", cmdp, NULL});
		if (!access(exe, X_OK) && !stat(exe, &st) && !S_ISDIR(st.st_mode))
			return (exe);
		free(exe);
	}
	return (NULL);
}

static char	*get_relexe(char **cmdp, t_vec *envs, const char **texts,
			t_shell *shell)
{
	char	**dirs;
	char	*path;
	char	*exe;

	path = get_enval(envs, "PATH");
	if (!path)
	{
		texts[1] = "No such file or directory";
		put_execerr(shell, texts, TRUE);
		free(cmdp);
		exit(127);
	}
	dirs = ft_split(path, ':');
	exe = get_exe(dirs, cmdp[0]);
	free_strs(dirs);
	if (!exe)
	{
		texts[1] = "command not found";
		put_execerr(shell, texts, !get_shellmode(READ));
		free(cmdp);
		exit(127);
	}
	return (exe);
}

static char	*get_absexe(char **cmdp, const char **texts, t_shell *shell)
{
	struct stat	st;

	if (access(cmdp[0], F_OK) != 0)
	{
		texts[1] = strerror(errno);
		put_execerr(shell, texts, TRUE);
		free(cmdp);
		exit(127);
	}
	if (stat(cmdp[0], &st) == 0 && S_ISDIR(st.st_mode))
	{
		texts[1] = "Is a directory";
		put_execerr(shell, texts, TRUE);
		free(cmdp);
		exit(126);
	}
	else if (access(cmdp[0], X_OK) != 0)
	{
		texts[1] = strerror(errno);
		put_execerr(shell, texts, TRUE);
		free(cmdp);
		exit(126);
	}
	return (ft_strdup(cmdp[0]));
}
