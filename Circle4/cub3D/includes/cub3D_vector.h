/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D_vector.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ucho <ucho@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/09 05:15:53 by ucho              #+#    #+#             */
/*   Updated: 2026/07/09 05:15:54 by ucho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_VECTOR_H
# define CUB3D_VECTOR_H

# include <stddef.h>

typedef void	(*t_free)(void *elem);

typedef struct s_vec
{
	void		*data;
	long long	len;
	long long	cap;
	long long	size;
	t_free		free;
}	t_vec;

void	*vec_at(t_vec *vec, long long i);
void	vec_free(t_vec *vec);
int		vec_init(t_vec *vec, long long size, long long cap, t_free free);
int		vec_push(t_vec *vec, const void *elem);
int		vec_copy(t_vec *dst, t_vec *src);

#endif
