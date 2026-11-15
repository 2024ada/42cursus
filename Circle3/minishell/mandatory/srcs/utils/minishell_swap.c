/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_swap.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ucho <ucho@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 12:56:46 by ucho              #+#    #+#             */
/*   Updated: 2026/01/29 04:24:39 by ucho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_swap(void *a, void *b, long long size)
{
	unsigned char	tmp;
	t_idx			i;

	i = 0;
	while (i < size)
	{
		tmp = ((unsigned char *)a)[i];
		((unsigned char *)a)[i] = ((unsigned char *)b)[i];
		((unsigned char *)b)[i] = tmp;
		i++;
	}
}

void	ft_sort(t_vec *vec, long long offset, int is_ptr)
{
	char	*a;
	char	*b;
	t_idx	i;
	t_idx	j;

	if (!vec || vec->len < 2 || !vec->size)
		return ;
	i = 0;
	while (i < vec->len - 1)
	{
		j = i + 1;
		while (j < vec->len)
		{
			a = vec_to_str(vec, i, offset, is_ptr);
			b = vec_to_str(vec, j, offset, is_ptr);
			if (ft_strcmp(a, b) > 0)
				ft_swap(vec_at(vec, i), vec_at(vec, j), vec->size);
			j++;
		}
		i++;
	}
}

char	*vec_to_str(t_vec *vec, t_idx i, long long ofs, int is_ptr)
{
	void	*elem;
	char	*str;

	elem = vec_at(vec, i);
	if (!elem)
		return (NULL);
	str = (char *)elem + ofs;
	if (is_ptr)
		return (*(char **)str);
	else
		return (str);
}
