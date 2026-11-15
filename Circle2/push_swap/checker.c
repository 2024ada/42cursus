/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ucho <ucho@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 14:54:34 by ucho              #+#    #+#             */
/*   Updated: 2025/07/29 23:07:07 by ucho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	set_operation(char *operation, t_stack *a, t_stack *b)
{
	if (!ft_strncmp(operation, "sa\n", 3))
		swap(a->array, a->size);
	else if (!ft_strncmp(operation, "sb\n", 3))
		swap(b->array, b->size);
	else if (!ft_strncmp(operation, "ss\n", 3))
		swap_both(a, b);
	else if (!ft_strncmp(operation, "pa\n", 3))
		push(b, a);
	else if (!ft_strncmp(operation, "pb\n", 3))
		push(a, b);
	else if (!ft_strncmp(operation, "ra\n", 3))
		rotate(a);
	else if (!ft_strncmp(operation, "rb\n", 3))
		rotate(b);
	else if (!ft_strncmp(operation, "rr\n", 3))
		rotate_both(a, b);
	else if (!ft_strncmp(operation, "rra\n", 4))
		reverse_rotate(a);
	else if (!ft_strncmp(operation, "rrb\n", 4))
		reverse_rotate(b);
	else if (!ft_strncmp(operation, "rrr\n", 4))
		reverse_rotate_both(a, b);
	else
		return (FALSE);
	return (TRUE);
}

int	get_operation(t_stack *a, t_stack *b)
{
	char	*line;

	line = get_next_line(0);
	while (line != NULL)
	{
		if (!set_operation(line, a, b))
		{
			free(line);
			return (FALSE);
		}
		free(line);
		line = get_next_line(0);
	}
	return (TRUE);
}

int	exit_checker(int code)
{
	get_next_line(-42);
	return (code);
}

int	checker(t_stack *a, char **raw)
{
	t_stack	b;

	if (!get_stack(a, *raw))
		return (exit_checker(ERROR));
	b.array = malloc(sizeof(int) * a->size);
	if (!b.array)
	{
		free(a->array);
		return (exit_checker(ERROR));
	}
	b.size = 0;
	if (!get_operation(a, &b))
	{
		(free(a->array), free(b.array));
		return (exit_checker(ERROR));
	}
	if (is_sorted(a))
	{
		(free(a->array), free(b.array));
		return (exit_checker(TRUE));
	}
	(free(a->array), free(b.array));
	return (exit_checker(FALSE));
}

int	main(int argc, char **argv)
{
	t_stack	a;
	char	*raw;
	int		i;
	int		check;

	if (argc <= 1)
		exit(-1);
	raw = ft_strdup("");
	if (!raw)
		return (put_result(ERROR));
	i = 1;
	while (i < argc)
	{
		if (!parse_tokens(&raw, argv[i]))
			return (free(raw), put_result(ERROR));
		i++;
	}
	check = checker(&a, &raw);
	if (check == TRUE)
		return (free(raw), put_result(TRUE));
	else if (check == FALSE)
		return (free(raw), put_result(FALSE));
	else
		return (free(raw), put_result(ERROR));
}
