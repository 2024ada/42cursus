/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_convert.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ucho <ucho@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 00:00:00 by ucho              #+#    #+#             */
/*   Updated: 2026/01/29 04:27:31 by ucho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_CONVERT_H
# define MINISHELL_CONVERT_H

# include "minishell_vector.h"
# include "minishell_parse.h"

typedef struct s_shell	t_shell;

char	*vec_to_str(t_vec *vec, t_idx i, long long ofs, int is_ptr);

char	**cmdline_to_cmdp(t_cmdline *cmdline);

t_vec	*envp_to_envs(char **envp);
char	**envs_to_envp(t_vec *envs);

void	slash_to_star(char *str);
void	star_to_slash(char *tok);

char	*node_to_str(t_node *node);

#endif
