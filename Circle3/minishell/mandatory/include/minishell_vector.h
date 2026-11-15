/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_vector.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ucho <ucho@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 00:00:00 by ucho              #+#    #+#             */
/*   Updated: 2026/01/29 04:27:16 by ucho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_VECTOR_H
# define MINISHELL_VECTOR_H

typedef long long				t_idx;
typedef void					(*t_free)(void *elem);

typedef struct s_vec
{
	void		*data;
	long long	len;
	long long	cap;
	long long	size;
	t_free		free;
}	t_vec;

void	*vec_at(t_vec *vec, t_idx i);
void	vec_free(t_vec *vec);
int		vec_reserve(t_vec *vec, long long new_cap);
int		vec_init(t_vec *vec, long long size, long long cap, t_free free);
int		vec_push(t_vec *vec, const void *elem);

#endif
