/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_wildcard_bonus.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ucho <ucho@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 15:47:26 by ucho              #+#    #+#             */
/*   Updated: 2026/01/29 04:23:05 by ucho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

int			get_dirents(const char *path, t_vec *ents);
static int	cast_wildcard(char **segs, t_vec *hits, t_vec *cands);
static int	cast_wildcard_match(char *base, char *pattern, t_vec *cands);
static int	cast_wildcard_fill(char *base, char **segs, t_vec *cands);

int	run_glob(t_glob *glob)
{
	t_vec	cands;
	t_idx	i;

	i = -1;
	while (glob->segs[++i])
	{
		if (glob->segs[i + 1] == NULL)
		{
			if (glob->hits.len == 1)
				glob->prefix = ft_strdup(vec_to_str(&glob->hits, 0, 0, TRUE));
		}
		vec_init(&cands, sizeof(char *), 16, free_str);
		cast_wildcard(&glob->segs[i], &glob->hits, &cands);
		vec_free(&glob->hits);
		glob->hits = cands;
		if (glob->hits.len == 0 && glob->segs[i + 1] != NULL)
			break ;
	}
	return (TRUE);
}

static int	cast_wildcard(char **segs, t_vec *hits, t_vec *cands)
{
	char	*base;
	t_idx	i;

	i = 0;
	while (i < hits->len)
	{
		base = vec_to_str(hits, i, 0, TRUE);
		if (ft_strchr(segs[0], '*'))
			cast_wildcard_match(base, segs[0], cands);
		else
			cast_wildcard_fill(base, segs, cands);
		i++;
	}
	return (TRUE);
}

static int	is_match(const char *pattern, const char *str)
{
	while (*pattern && *str)
	{
		if (*pattern == '*')
		{
			while (*pattern == '*')
				pattern++;
			if (!*pattern)
				return (TRUE);
			while (*str)
				if (is_match(pattern, str++))
					return (TRUE);
			return (FALSE);
		}
		if (*pattern != *str)
		{
			if (!(*str == '*' && *pattern == '/'))
				return (FALSE);
		}
		pattern++;
		str++;
	}
	while (*pattern == '*')
		pattern++;
	return (!*pattern && !*str);
}

static int	cast_wildcard_match(char *base, char *pattern, t_vec *cands)
{
	t_vec	dirents;
	char	*dirent;
	char	*path;
	t_idx	i;

	if (!get_dirents(base, &dirents))
		return (TRUE);
	i = 0;
	while (i < dirents.len)
	{
		dirent = vec_to_str(&dirents, i++, 0, TRUE);
		if (dirent[0] == '.' && pattern[0] != '.')
			continue ;
		if (is_match(pattern, dirent))
		{
			if (base[ft_strlen(base) - 1] == '/')
				path = ft_strsjoin((char *[]){base, dirent, NULL});
			else
				path = ft_strsjoin((char *[]){base, "/", dirent, NULL});
			vec_push(cands, &path);
		}
	}
	return (vec_free(&dirents), TRUE);
}

static int	cast_wildcard_fill(char *base, char **segs, t_vec *cands)
{
	char	*path;
	DIR		*dir;
	t_idx	i;

	if (segs[0])
	{
		i = -1;
		while (segs[0][++i])
			if (segs[0][i] == '/')
				segs[0][i] = '*';
	}
	if (base[ft_strlen(base) - 1] == '/')
		path = ft_strsjoin((char *[]){base, segs[0], NULL});
	else
		path = ft_strsjoin((char *[]){base, "/", segs[0], NULL});
	if ((segs[1]) != NULL)
	{
		dir = opendir(path);
		if (!dir)
			return (free(path), TRUE);
		closedir(dir);
	}
	vec_push(cands, &path);
	return (TRUE);
}
