/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_d.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ucho <ucho@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 03:21:44 by ucho              #+#    #+#             */
/*   Updated: 2025/01/23 20:23:59 by ucho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	put_int(va_list args, int *bytes, t_flag *flag)
{
	int			d;
	char		*s;
	long long	size;
	int			span;
	int			sign;

	d = va_arg(args, int);
	sign = 0;
	if (d < 0 || flag->plus)
	{
		sign = 1;
		flag->space = 0;
	}
	size = ft_intlen(d);
	span = filter_flag(sign, &size, d, flag);
	s = get_int(d, size, flag->plus);
	span += get_space(d, bytes, s, flag);
	if (!flag->minus)
		put_space(span);
	write(STDOUT_FILENO, s, ft_strlen(s));
	if (flag->minus)
		put_space(span);
	(*bytes) += (ft_strlen(s) + span);
	free(s);
}

int	ft_intlen(int nbr)
{
	long long	n;
	long long	divisor;
	int			bytes;

	divisor = 1;
	bytes = 1;
	n = nbr;
	if (nbr < 0)
		n = -n;
	while (n / divisor >= 10)
	{
		divisor *= 10;
		bytes++;
	}
	return (bytes);
}

int	get_space(int d, int *bytes, char *s, t_flag *flag)
{
	int	span;

	span = 0;
	if (flag->zero && flag->width > ft_intlen(d) && flag->space)
		s[0] = ' ';
	else if (flag->space && !span)
	{
		write(STDOUT_FILENO, " ", 1);
		(*bytes)++;
	}
	if (flag->minus && flag->space && span)
	{
		write(STDOUT_FILENO, " ", 1);
		(*bytes)++;
		span--;
	}
	return (span);
}

char	*get_int(long long n, long long size, int plus)
{
	char		*result;
	long long	nbr;
	long long	i;

	result = (char *)malloc(size + 1);
	if (!result)
		return (NULL);
	nbr = n;
	i = size;
	if (n < 0)
		nbr = -nbr;
	result[i--] = '\0';
	while (nbr > 0)
	{
		result[i--] = (nbr % 10) + '0';
		nbr /= 10;
	}
	while (i >= 0)
		result[i--] = '0';
	if (n < 0)
		result[0] = '-';
	else if (plus)
		result[0] = '+';
	return (result);
}
