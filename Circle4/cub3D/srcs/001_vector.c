/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   001_vector.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ucho <ucho@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/09 04:47:49 by ucho              #+#    #+#             */
/*   Updated: 2026/07/09 04:47:49 by ucho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

void	*vec_at(t_vec *vec, long long i)
{
	if (!vec || i >= vec->len)
		return (NULL);
	return ((char *)vec->data + (i * vec->size));
}

void	vec_free(t_vec *vec)
{
	void		*elem;
	long long	i;

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

int	vec_init(t_vec *vec, long long size, long long cap, t_free free)
{
	if (!vec || size == 0 || cap < 0)
		return (FALSE);
	vec->data = NULL;
	vec->len = 0;
	vec->cap = cap;
	vec->size = size;
	vec->free = free;
	if (cap > 0)
		vec->data = ft_xmalloc(size * cap);
	return (TRUE);
}

int	vec_push(t_vec *vec, const void *elem)
{
	long long	new_cap;
	void		*data;
	void		*dst;

	if (!vec || !elem)
		return (FALSE);
	if (vec->len == vec->cap)
	{
		if (vec->cap == 0)
			new_cap = 1;
		else
			new_cap = vec->cap * 2;
		data = ft_xmalloc(vec->size * new_cap);
		if (vec->data && vec->len > 0)
			ft_memcpy(data, vec->data, vec->size * vec->len);
		free(vec->data);
		vec->data = data;
		vec->cap = new_cap;
	}
	dst = (char *)vec->data + (vec->len * vec->size);
	ft_memcpy(dst, elem, vec->size);
	vec->len++;
	return (TRUE);
}

int	vec_copy(t_vec *dst, t_vec *src)
{
	void		*elem;
	long long	i;

	if (!dst || !src || dst->size != src->size)
		return (FALSE);
	if (dst == src)
		return (TRUE);
	if (dst->free)
	{
		i = -1;
		while (++i < dst->len)
		{
			elem = vec_at(dst, i);
			if (elem)
				dst->free(elem);
		}
	}
	(void)(TRUE &&(dst->len = 0, i = -1));
	while (++i < src->len)
	{
		elem = vec_at(src, i);
		if (elem && !vec_push(dst, elem))
			return (FALSE);
	}
	return (TRUE);
}
