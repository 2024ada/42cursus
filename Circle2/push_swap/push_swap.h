/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ucho <ucho@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 18:19:05 by ucho              #+#    #+#             */
/*   Updated: 2025/07/29 23:06:46 by ucho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include "libft/libft.h"
# include "ft_printf/ft_printf.h"
# include "get_next_line/get_next_line.h"
# include <stdlib.h>
# include <unistd.h>
# define TRUE 1
# define FALSE 0
# define ERROR -1
# define INT_MIN -2147483648
# define INT_MAX 2147483647

typedef struct s_stack
{
	int	*array;
	int	size;
}	t_stack;

typedef struct s_cost
{
	int	*b;
	int	*a;
	int	*total;
}	t_cost;

char		*ft_strcjoin(char const *s1, char const *s2, char *charset);
long long	ft_atoll(const char *nptr);
int			check_duplicate(int *array, int *pos, int number);
int			parse_values(int *array, char const *raw);
int			get_stack(t_stack *stack, char *raw);
int			put_result(int is_ok);
int			get_size(char const *raw);
void		pattern_sort(t_stack *a, t_stack *b);
void		extract_sort(t_stack *a, t_stack *b);
void		simple_sort(t_stack *a, t_stack *b);
void		get_table(t_stack *a, int *len_table, int *trace_table);
void		get_lis(t_stack *a, int *len_table, int *trace_table, int *is_lis);
int			get_slot(t_stack *stack, int value);
void		get_cost(t_cost *costs, int i, int b_val, int a_val);
int			*set_cost(int i, int slot, int asize, int bsize);
void		set_best(t_stack *a, t_stack *b, t_cost *costs);
int			get_best(t_stack *a, t_stack *b, t_cost *costs);
void		split_stack(t_stack *a, t_stack *b, int *is_lis);
void		rotate_stack(int *cost_a, int *cost_b, t_stack *a, t_stack *b);
void		merge_stack(t_stack *a, t_stack *b);
void		lis_sort(t_stack *a, t_stack *b, int *is_lis);
void		greedy_sort(t_stack *a, t_stack *b);
int			is_sorted(t_stack *stack);
int			get_min(int *array, int size);
int			get_abs(int num);
int			swap(int *array, int size);
void		push(t_stack *src, t_stack *dest);
int			rotate(t_stack *stack);
int			reverse_rotate(t_stack *stack);
int			put_operation(int num, t_stack *a, t_stack *b);
int			swap_both(t_stack *a, t_stack *b);
int			rotate_both(t_stack *a, t_stack *b);
int			reverse_rotate_both(t_stack *a, t_stack *b);
int			append_tokens(char **raw, char **tokens);
int			parse_tokens(char **raw, const char *arg);
int			is_valid(char **tokens);

#endif
