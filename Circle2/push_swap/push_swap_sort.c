/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_sort.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ucho <ucho@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 16:56:53 by ucho              #+#    #+#             */
/*   Updated: 2025/05/07 14:23:22 by ucho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	pattern_sort(t_stack *a, t_stack *b)
{
	int	i;

	i = 0;
	while (i < a->size)
	{
		if (is_sorted(a))
			break ;
		if (a->array[0] > a->array[1])
			put_operation(1, a, b);
		else if (a->array[1] > a->array[2])
			put_operation(9, a, b);
		i++;
	}
}

void	extract_sort(t_stack *a, t_stack *b)
{
	while (a->size > 3)
	{
		if (get_min(a->array, a->size) <= a->size - get_min(a->array, a->size))
		{
			while (get_min(a->array, a->size) != 0)
				put_operation(6, a, b);
		}
		else
		{
			while (get_min(a->array, a->size) != 0)
				put_operation(9, a, b);
		}
		put_operation(5, a, b);
	}
	pattern_sort(a, b);
	while (b->size > 0)
		put_operation(4, a, b);
}

void	simple_sort(t_stack *a, t_stack *b)
{
	if (a->size <= 3)
		pattern_sort(a, b);
	else
		extract_sort(a, b);
}

void	lis_sort(t_stack *a, t_stack *b, int *is_lis)
{
	int	*len_table;
	int	*trace_table;

	len_table = (int *)malloc(sizeof(int) * a->size);
	trace_table = (int *)malloc(sizeof(int) * a->size);
	if (!len_table || !trace_table)
	{
		free(len_table);
		free(trace_table);
		return ;
	}
	get_table(a, len_table, trace_table);
	get_lis(a, len_table, trace_table, is_lis);
	split_stack(a, b, is_lis);
	while (b->size > 0)
		merge_stack(a, b);
	while (!is_sorted(a))
	{
		if (get_min(a->array, a->size) <= a->size - get_min(a->array, a->size))
			put_operation(6, a, b);
		else
			put_operation(9, a, b);
	}
	free(len_table);
	free(trace_table);
}

void	greedy_sort(t_stack *a, t_stack *b)
{
	int	*is_lis;

	is_lis = malloc(sizeof(int) * a->size);
	if (!is_lis)
		return ;
	lis_sort(a, b, is_lis);
	free(is_lis);
}
