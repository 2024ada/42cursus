/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_ops_extra.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ucho <ucho@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 19:01:40 by ucho              #+#    #+#             */
/*   Updated: 2025/07/29 23:06:30 by ucho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	swap_both(t_stack *a, t_stack *b)
{
	swap(a->array, a->size);
	swap(b->array, b->size);
	return (1);
}

int	rotate_both(t_stack *a, t_stack *b)
{
	rotate(a);
	rotate(b);
	return (1);
}

int	reverse_rotate_both(t_stack *a, t_stack *b)
{
	reverse_rotate(a);
	reverse_rotate(b);
	return (1);
}

int	is_sorted(t_stack *stack)
{
	int	i;

	i = 0;
	while (i < stack->size - 1)
	{
		if (stack->array[i] > stack->array[i + 1])
			return (FALSE);
		i++;
	}
	return (TRUE);
}
