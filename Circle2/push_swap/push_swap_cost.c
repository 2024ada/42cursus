/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_cost.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ucho <ucho@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 16:20:44 by ucho              #+#    #+#             */
/*   Updated: 2025/05/07 14:20:52 by ucho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	get_slot(t_stack *stack, int value)
{
	int	i;
	int	before;
	int	after;

	if (stack->size == 0)
		return (0);
	i = 0;
	while (i < stack->size)
	{
		before = stack->array[i];
		after = stack->array[(i + 1) % stack->size];
		if (before < after && before < value && value < after)
			return ((i + 1) % stack->size);
		if (before > after && (before < value || value < after))
			return ((i + 1) % stack->size);
		i++;
	}
	return (0);
}

void	get_cost(t_cost *costs, int i, int b_val, int a_val)
{
	costs->b[i] = b_val;
	costs->a[i] = a_val;
}

int	*set_cost(int i, int slot, int asize, int bsize)
{
	int	*move;

	move = malloc(sizeof(int) * 4);
	if (!move)
		return (NULL);
	if (i < slot)
		move[0] = slot;
	else
		move[0] = i;
	if (i - bsize > slot - asize)
		move[1] = -(slot - asize);
	else
		move[1] = -(i - bsize);
	move[2] = i - (slot - asize);
	move[3] = slot - (i - bsize);
	return (move);
}

void	set_best(t_stack *a, t_stack *b, t_cost *costs)
{
	int	i;
	int	slot;
	int	min;
	int	*move;

	i = -1;
	while (++i < b->size)
	{
		slot = get_slot(a, b->array[i]);
		move = set_cost(i, slot, a->size, b->size);
		if (!move)
			continue ;
		min = get_min(move, 4);
		costs->total[i] = move[min];
		if (min == 0)
			get_cost(costs, i, i, slot);
		else if (min == 1)
			get_cost(costs, i, i - b->size, slot - a->size);
		else if (min == 2)
			get_cost(costs, i, i, slot - a->size);
		else
			get_cost(costs, i, i - b->size, slot);
		free(move);
	}
}

int	get_best(t_stack *a, t_stack *b, t_cost *costs)
{
	int	i;
	int	best;

	set_best(a, b, costs);
	best = 0;
	i = 1;
	while (i < b->size)
	{
		if (costs->total[i] < costs->total[best]
			|| (costs->total[i] == costs->total[best]
				&& get_abs(costs->b[i]) < get_abs(costs->b[best])))
			best = i;
		i++;
	}
	return (best);
}
