/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_ops.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ucho <ucho@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 20:54:25 by ucho              #+#    #+#             */
/*   Updated: 2025/07/29 23:06:57 by ucho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	swap(int *array, int size)
{
	int	temp;

	if (size < 2)
		return (1);
	temp = array[0];
	array[0] = array[1];
	array[1] = temp;
	return (1);
}

void	push(t_stack *src, t_stack *dst)
{
	if (src->size < 1)
		return ;
	dst->size++;
	if (dst->size > 0)
		ft_memmove(dst->array + 1, dst->array, sizeof(int) * (dst->size - 1));
	dst->array[0] = src->array[0];
	ft_memmove(src->array, src->array + 1, sizeof(int) * (src->size - 1));
	src->size--;
}

int	rotate(t_stack *stack)
{
	int	temp;

	if (stack->size < 2)
		return (1);
	temp = stack->array[0];
	ft_memmove(stack->array, stack->array + 1, sizeof(int) * (stack->size - 1));
	stack->array[stack->size - 1] = temp;
	return (1);
}

int	reverse_rotate(t_stack *stack)
{
	int	temp;

	if (stack->size < 2)
		return (1);
	temp = stack->array[stack->size - 1];
	ft_memmove(stack->array + 1, stack->array, sizeof(int) * (stack->size - 1));
	stack->array[0] = temp;
	return (1);
}

int	put_operation(int num, t_stack *a, t_stack *b)
{
	if (num == 1 && ft_printf("sa\n"))
		swap(a->array, a->size);
	else if (num == 2 && ft_printf("sb\n"))
		swap(b->array, b->size);
	else if (num == 3 && ft_printf("ss\n"))
		swap_both(a, b);
	else if (num == 4 && ft_printf("pa\n"))
		push(b, a);
	else if (num == 5 && ft_printf("pb\n"))
		push(a, b);
	else if (num == 6 && ft_printf("ra\n"))
		rotate(a);
	else if (num == 7 && ft_printf("rb\n"))
		rotate(b);
	else if (num == 8 && ft_printf("rr\n"))
		rotate_both(a, b);
	else if (num == 9 && ft_printf("rra\n"))
		reverse_rotate(a);
	else if (num == 10 && ft_printf("rrb\n"))
		reverse_rotate(b);
	else if (num == 11 && ft_printf("rrr\n"))
		reverse_rotate_both(a, b);
	return (1);
}
