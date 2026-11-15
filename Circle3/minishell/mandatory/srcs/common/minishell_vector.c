/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_vector.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ucho <ucho@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 13:21:07 by ucho              #+#    #+#             */
/*   Updated: 2026/01/29 04:26:59 by ucho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*vec_at(t_vec *vec, t_idx i)
{
	if (!vec || i >= vec->len)
		return (NULL);
	return ((char *)vec->data + (i * vec->size));
}

void	vec_free(t_vec *vec)
{
	void	*elem;
	t_idx	i;

	if (!vec)
		return ;
	if (vec->free)
	{
		i = 0;
		while (i < vec->len)
		{
			elem = vec_at(vec, i);
			if (elem)
				vec->free(elem);
			i++;
		}
	}
	free(vec->data);
	vec->data = NULL;
	vec->len = 0;
	vec->cap = 0;
	vec->size = 0;
}

int	vec_reserve(t_vec *vec, long long new_cap)
{
	void	*nv;

	if (!vec || new_cap <= vec->cap)
		return (TRUE);
	nv = ft_xmalloc(vec->size * new_cap);
	ft_memcpy(nv, vec->data, vec->size * vec->len);
	free(vec->data);
	vec->data = nv;
	vec->cap = new_cap;
	return (TRUE);
}

int	vec_init(t_vec *vec, long long size, long long cap, t_free free)
{
	if (!vec || size == 0)
		return (FALSE);
	if (cap == 0)
		cap = 1;
	vec->data = ft_xmalloc(size * cap);
	vec->len = 0;
	vec->cap = cap;
	vec->size = size;
	vec->free = free;
	return (TRUE);
}

int	vec_push(t_vec *vec, const void *elem)
{
	long long	new_cap;
	void		*dst;

	if (!vec || !elem)
		return (FALSE);
	if (vec->len == vec->cap)
	{
		if (vec->cap == 0)
			new_cap = 1;
		else
			new_cap = vec->cap * 2;
		vec_reserve(vec, new_cap);
	}
	dst = (char *)vec->data + (vec->len * vec->size);
	ft_memcpy(dst, elem, vec->size);
	vec->len++;
	return (TRUE);
}
