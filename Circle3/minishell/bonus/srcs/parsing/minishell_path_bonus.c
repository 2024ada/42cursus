/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_path_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ucho <ucho@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 15:49:05 by ucho              #+#    #+#             */
/*   Updated: 2026/01/29 04:20:47 by ucho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

int	get_dirents(const char *path, t_vec *dirents)
{
	DIR				*dir;
	struct dirent	*ents;
	char			*name;

	vec_init(dirents, sizeof(char *), 16, free_str);
	dir = opendir(path);
	if (!dir)
		return (vec_free(dirents), FALSE);
	ents = readdir(dir);
	while (ents)
	{
		name = ft_strdup(ents->d_name);
		vec_push(dirents, &name);
		ents = readdir(dir);
	}
	closedir(dir);
	ft_sort(dirents, 0, TRUE);
	return (TRUE);
}

char	*join_path(t_vec *segs)
{
	char	*res;
	char	*tmp;
	char	*seg;
	t_idx	i;

	res = ft_strdup("/");
	i = 0;
	while (i < segs->len && res)
	{
		seg = vec_to_str(segs, i, 0, TRUE);
		tmp = res;
		if (res[ft_strlen(res) - 1] == '/')
			res = ft_strsjoin((char *[]){res, seg, NULL});
		else
			res = ft_strsjoin((char *[]){res, "/", seg, NULL});
		free(tmp);
		i++;
	}
	return (res);
}

char	*trim_path(char *path)
{
	char		**paths;
	t_vec		segs;
	char		*res;
	t_idx		i;

	if (!path || *path != '/')
		return (NULL);
	paths = ft_split(path, '/');
	vec_init(&segs, sizeof(char *), 16, NULL);
	i = -1;
	while (paths[++i])
	{
		if (ft_strcmp(paths[i], "..") == 0)
		{
			if (segs.len > 0)
				segs.len--;
		}
		else if (ft_strcmp(paths[i], ".") != 0)
			vec_push(&segs, &paths[i]);
	}
	res = join_path(&segs);
	return (free_strs(paths), vec_free(&segs), free(path), res);
}
