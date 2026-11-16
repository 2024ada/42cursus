/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ucho <ucho@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 03:21:26 by ucho              #+#    #+#             */
/*   Updated: 2025/01/23 20:24:03 by ucho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	filter_flag(int marker, long long *size, long long n, t_flag *flag)
{
	int	span;

	span = 0;
	if (flag->zero && (flag->minus || flag->point || !flag->width))
		flag->zero = 0;
	if (flag->width <= *size + marker
		|| flag->width <= flag->precision + marker)
		flag->width = 0;
	if (flag->precision <= *size
		&& !(!n && flag->point && flag->precision < *size))
		flag->precision = *size;
	if (!flag->point && flag->zero && flag->width > *size)
		*size = flag->width;
	else
		*size = marker + flag->precision;
	if (flag->width > *size)
		span = flag->width - *size;
	return (span);
}

int	put_flag(int*bytes, t_flag *flag)
{
	if (!flag)
		return (0);
	write(STDOUT_FILENO, "%", 1);
	(*bytes)++;
	if (flag->plus)
		flag->space = 0;
	if (flag->minus || flag->point)
		flag->zero = 0;
	if (flag->sharp == 1 && write(STDOUT_FILENO, "#", 1))
		(*bytes)++;
	if (flag->plus == 1 && write(STDOUT_FILENO, "+", 1))
		(*bytes)++;
	if (flag->space == 1 && write(STDOUT_FILENO, " ", 1))
		(*bytes)++;
	if (flag->zero == 1 && write(STDOUT_FILENO, "0", 1))
		(*bytes)++;
	if (flag->minus == 1 && write(STDOUT_FILENO, "-", 1))
		(*bytes)++;
	if (flag->width > 0)
		(*bytes) += put_field(flag->width);
	if (flag->point == 1 && write(STDOUT_FILENO, ".", 1))
		(*bytes) += put_field(flag->precision) + 1;
	return (1);
}

int	put_field(int num)
{
	ft_putnbr_fd(num, 1);
	return (ft_intlen(num));
}
