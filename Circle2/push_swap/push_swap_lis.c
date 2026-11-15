/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_lis.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ucho <ucho@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 16:26:42 by ucho              #+#    #+#             */
/*   Updated: 2025/05/07 14:20:54 by ucho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	get_table(t_stack *a, int *len_table, int *trace_table)
{
	int	i;
	int	j;

	i = 0;
	while (i < a->size)
	{
		len_table[i] = 1;
		trace_table[i++] = -1;
	}
	i = 0;
	while (i < a->size)
	{
		j = 0;
		while (j < i)
		{
			if (a->array[j] < a->array[i] && len_table[j] + 1 > len_table[i])
			{
				len_table[i] = len_table[j] + 1;
				trace_table[i] = j;
			}
			j++;
		}
		i++;
	}
}

void	get_lis(t_stack *a, int *len_table, int *trace_table, int *is_lis)
{
	int	i;
	int	len;
	int	last;

	i = 0;
	while (i < a->size)
		is_lis[i++] = FALSE;
	len = 0;
	last = 0;
	i = 0;
	while (i < a->size)
	{
		if (len_table[i] > len)
		{
			len = len_table[i];
			last = i;
		}
		i++;
	}
	while (last != -1)
	{
		is_lis[last] = TRUE;
		last = trace_table[last];
	}
}

void	split_stack(t_stack *a, t_stack *b, int *is_lis)
{
	int	i;
	int	size;

	size = a->size;
	i = 0;
	while (i < size)
	{
		if (is_lis[i])
			put_operation(6, a, b);
		else
			put_operation(5, a, b);
		i++;
	}
}

void	merge_stack(t_stack *a, t_stack *b)
{
	t_cost	costs;
	int		best;

	if (b->size == 0)
		return ;
	costs.b = malloc(sizeof(int) * b->size);
	costs.a = malloc(sizeof(int) * b->size);
	costs.total = malloc(sizeof(int) * b->size);
	if (!costs.b || !costs.a || !costs.total)
	{
		free(costs.b);
		free(costs.a);
		free(costs.total);
		return ;
	}
	best = get_best(a, b, &costs);
	rotate_stack(&costs.a[best], &costs.b[best], a, b);
	put_operation(4, a, b);
	free(costs.b);
	free(costs.a);
	free(costs.total);
}

void	rotate_stack(int *cost_a, int *cost_b, t_stack *a, t_stack *b)
{
	while (*cost_b > 0 && *cost_a > 0 && put_operation(8, a, b))
	{
		(*cost_b)--;
		(*cost_a)--;
	}
	while (*cost_b < 0 && *cost_a < 0 && put_operation(11, a, b))
	{
		(*cost_b)++;
		(*cost_a)++;
	}
	while (*cost_b > 0 && put_operation(7, a, b))
		(*cost_b)--;
	while (*cost_b < 0 && put_operation(10, a, b))
		(*cost_b)++;
	while (*cost_a > 0 && put_operation(6, a, b))
		(*cost_a)--;
	while (*cost_a < 0 && put_operation(9, a, b))
		(*cost_a)++;
}
