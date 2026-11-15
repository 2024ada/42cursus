/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_wildcard.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ucho <ucho@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 00:00:00 by ucho              #+#    #+#             */
/*   Updated: 2026/01/29 04:27:15 by ucho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_WILDCARD_H
# define MINISHELL_WILDCARD_H

# include "minishell_vector.h"

typedef struct s_glob
{
	char	*pattern;
	t_vec	hits;
	char	**segs;
	char	*prefix;
	int		is_dir;
	int		stat;
}	t_glob;

t_glob	*do_glob(t_glob *glob, const char *path);
t_glob	*skip_glob(t_glob *glob);
void	set_glob(t_glob *glob, const char *path);
int		run_glob(t_glob *glob);
int		get_glob(t_glob *glob, const char *path);

char	*del_quote(const char *str, int *has_quote);

#endif
