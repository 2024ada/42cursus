/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_parse.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ucho <ucho@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 18:47:14 by ucho              #+#    #+#             */
/*   Updated: 2025/05/07 14:21:53 by ucho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	is_valid(char **tokens)
{
	int		i;
	int		start;

	while (*tokens)
	{
		i = 0;
		if (!*tokens || (*tokens)[0] == '\0')
			return (0);
		if ((*tokens)[i] == '+' || (*tokens)[i] == '-')
			i++;
		start = i;
		while ((*tokens)[i] >= '0' && (*tokens)[i] <= '9')
			i++;
		if (i == start || (*tokens)[i] != '\0')
			return (0);
		tokens++;
	}
	return (1);
}

int	parse_values(int *array, char const *raw)
{
	int			*pos;
	long long	number;

	pos = array;
	while (*raw)
	{
		if (*raw == ' ')
		{
			raw++;
			continue ;
		}
		number = ft_atoll(raw);
		if (number < INT_MIN || number > INT_MAX)
			return (FALSE);
		if (check_duplicate(array, pos, (int)number))
			return (FALSE);
		pos++;
		if (*raw == '+' || *raw == '-')
			raw++;
		while (*raw >= '0' && *raw <= '9')
			raw++;
	}
	return (TRUE);
}

int	check_duplicate(int *array, int *pos, int number)
{
	while (array < pos)
	{
		if (*array == number)
			return (TRUE);
		array++;
	}
	*pos = number;
	return (FALSE);
}

int	get_size(char const *raw)
{
	int	size;

	size = 0;
	while (*raw)
	{
		if (*raw == ' ')
		{
			raw++;
			continue ;
		}
		if (*raw == '+' || *raw == '-')
			raw++;
		while (*raw >= '0' && *raw <= '9')
			raw++;
		size++;
	}
	return (size);
}

int	get_stack(t_stack *stack, char *raw)
{
	stack->size = get_size(raw);
	stack->array = malloc(sizeof(int) * stack->size);
	if (!stack->array || !parse_values(stack->array, raw))
	{
		free(stack->array);
		return (FALSE);
	}
	return (TRUE);
}
