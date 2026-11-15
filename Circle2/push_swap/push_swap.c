/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ucho <ucho@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 18:19:05 by ucho              #+#    #+#             */
/*   Updated: 2025/05/08 02:37:44 by ucho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	push_swap(t_stack *a, char **raw)
{
	t_stack	b;

	if (!get_stack(a, *raw))
		return (FALSE);
	if (is_sorted(a))
	{
		free(a->array);
		return (TRUE);
	}
	b.array = malloc(sizeof(int) * a->size);
	if (!b.array)
	{
		free(a->array);
		return (FALSE);
	}
	b.size = 0;
	if (a->size <= 5)
		simple_sort(a, &b);
	else
		greedy_sort(a, &b);
	free(a->array);
	free(b.array);
	return (TRUE);
}

int	main(int argc, char **argv)
{
	t_stack	a;
	char	*raw;
	int		i;

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
	if (!push_swap(&a, &raw))
		return (free(raw), put_result(ERROR));
	free(raw);
	exit(0);
}
