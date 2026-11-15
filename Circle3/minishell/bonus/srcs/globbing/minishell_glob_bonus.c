/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_glob_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ucho <ucho@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 15:46:36 by ucho              #+#    #+#             */
/*   Updated: 2026/01/29 04:23:08 by ucho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

t_glob	*do_glob(t_glob *glob, const char *path)
{
	if (!ft_strchr(glob->pattern, '*'))
		return (skip_glob(glob));
	set_glob(glob, path);
	run_glob(glob);
	if (glob->hits.len == 0 && !glob->prefix)
		return (free_strs(glob->segs), free(glob->prefix), glob);
	get_glob(glob, path);
	return (free_strs(glob->segs), free(glob->prefix), glob);
}

t_glob	*skip_glob(t_glob *glob)
{
	char	*hit;

	vec_init(&glob->hits, sizeof(char *), 16, free_str);
	hit = ft_strdup(glob->pattern);
	vec_push(&glob->hits, &hit);
	glob->stat = TRUE;
	return (glob);
}

void	set_glob(t_glob *glob, const char *path)
{
	char	*seg;
	char	*base;
	t_idx	i;

	glob->segs = ft_split(path, '/');
	i = -1;
	while (glob->segs[++i])
	{
		(star_to_slash(glob->segs[i]), seg = del_quote(glob->segs[i], NULL));
		(free(glob->segs[i]), glob->segs[i] = seg);
	}
	vec_init(&glob->hits, sizeof(char *), 16, free_str);
	if (path && *path == '/')
	{
		i = 0;
		while (path[i] == '/')
			i++;
		if (i > 1 && path[i] != '\0')
			base = ft_substr(path, 0, i);
		else
			base = ft_strdup("/");
	}
	else
		base = ft_strdup(".");
	vec_push(&glob->hits, &base);
}

static int	add_slash(t_glob *glob)
{
	t_vec	cands;
	char	*hit;
	DIR		*dir;
	t_idx	i;

	vec_init(&cands, sizeof(char *), 16, free_str);
	i = -1;
	while (++i < glob->hits.len)
	{
		hit = ft_strdup(vec_to_str(&glob->hits, i, 0, TRUE));
		dir = opendir(hit);
		if (dir)
		{
			closedir(dir);
			ft_stradd(&hit, "/");
		}
		vec_push(&cands, &hit);
	}
	vec_free(&glob->hits);
	glob->hits = cands;
	return (TRUE);
}

int	get_glob(t_glob *glob, const char *path)
{
	char	*hit;
	char	**segs;

	glob->is_dir = (*path && path[ft_strlen(path) - 1] == '/');
	if (glob->is_dir)
		add_slash(glob);
	segs = glob->segs;
	while (*(segs + 1))
		segs++;
	if (glob->hits.len >= 1)
		glob->stat = glob->hits.len;
	else if (glob->prefix)
	{
		slash_to_star(*segs);
		if (glob->prefix[ft_strlen(glob->prefix) - 1] == '/')
			hit = ft_strsjoin((char *[]){glob->prefix, *segs, NULL});
		else
			hit = ft_strsjoin((char *[]){glob->prefix, "/", *segs, NULL});
		if (glob->is_dir)
			ft_stradd(&hit, "/");
		vec_push(&glob->hits, &hit);
		glob->stat = TRUE;
	}
	return (TRUE);
}
