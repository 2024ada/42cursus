/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_env.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ucho <ucho@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 00:00:00 by ucho              #+#    #+#             */
/*   Updated: 2026/01/29 04:27:30 by ucho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_ENV_H
# define MINISHELL_ENV_H

# include "minishell_vector.h"

typedef struct s_shell			t_shell;

typedef struct s_env
{
	char	*key;
	char	*val;
}	t_env;

void	add_env(t_vec *envs, const char *key, const char *val);
void	del_env(t_vec *envs, const char *key);
char	*cast_env(t_shell *shell, char *key);

char	*get_envar(t_shell *shell, const char *key);
char	*get_enval(t_vec *envs, const char *key);

#endif
