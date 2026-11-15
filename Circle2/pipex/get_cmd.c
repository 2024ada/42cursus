/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ucho <ucho@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 02:31:35 by ada               #+#    #+#             */
/*   Updated: 2025/07/31 03:58:59 by ucho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	let_strs(char **dirs)
{
	char	**dir;

	if (!dirs)
		return ;
	dir = dirs;
	while (*dir)
	{
		free(*dir);
		dir++;
	}
	free(dirs);
}

char	*get_path(char **envp)
{
	char	**path;

	path = envp;
	while (path && *path)
	{
		if (ft_strncmp(*path, "PATH=", 5) == 0)
			return (*path + 5);
		path++;
	}
	return ("/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin");
}

char	*get_exec(char *dir, const char *cmd)
{
	char	*temp;
	char	*target;

	if (ft_strchr(cmd, '/'))
		return (ft_strdup(cmd));
	temp = ft_strjoin(dir, "/");
	if (!temp)
		return (NULL);
	target = ft_strjoin(temp, cmd);
	free(temp);
	if (!target)
		return (NULL);
	return (target);
}

char	*get_cmd(const char *cmd, char **envp)
{
	char	*path;
	char	**dirs;
	int		i;
	char	*target;

	path = get_path(envp);
	if (!path)
		return (NULL);
	dirs = ft_split(path, ':');
	if (!dirs)
		return (NULL);
	i = 0;
	while (dirs[i])
	{
		target = get_exec(dirs[i], cmd);
		if (!target)
			break ;
		if (access(target, X_OK) == 0)
			break ;
		free(target);
		target = NULL;
		i++;
	}
	let_strs(dirs);
	return (target);
}
