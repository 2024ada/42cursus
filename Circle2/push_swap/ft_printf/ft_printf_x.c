/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_x.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ucho <ucho@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 03:21:59 by ucho              #+#    #+#             */
/*   Updated: 2025/01/23 20:24:05 by ucho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	put_hex(va_list args, int *bytes, t_flag *flag)
{
	unsigned int	x;
	char			*s;
	long long		size;
	int				span;
	int				sharp;

	x = va_arg(args, int);
	sharp = 0;
	if (flag->sharp && x != 0)
		sharp = 2;
	size = ft_hexlen(x);
	span = filter_flag(sharp, &size, x, flag);
	s = get_hex(x, size, flag->sharp, flag->is_uppercase);
	if (!flag->minus)
		put_space(span);
	write(STDOUT_FILENO, s, ft_strlen(s));
	if (flag->minus)
		put_space(span);
	(*bytes) += (ft_strlen(s) + span);
	free(s);
}

int	ft_hexlen(unsigned int nbr)
{
	unsigned int	n;
	unsigned int	divisor;
	int				bytes;

	divisor = 1;
	bytes = 1;
	n = nbr;
	while (n / divisor >= 16)
	{
		divisor *= 16;
		bytes++;
	}
	return (bytes);
}

char	*get_hex(unsigned int n, long long size, int sharp, int is_uppercase)
{
	char			*hex;
	char			*result;
	unsigned int	nbr;
	long long		i;

	hex = "0123456789abcdef";
	if (is_uppercase)
		hex = "0123456789ABCDEF";
	result = (char *)malloc(size + 1);
	if (!result)
		return (NULL);
	nbr = n;
	i = size;
	result[i--] = '\0';
	while (nbr > 0)
	{
		result[i--] = hex[nbr % 16];
		nbr /= 16;
	}
	while (i >= 0)
		result[i--] = '0';
	if (sharp && n != 0)
		result[1] = 'x' - is_uppercase;
	return (result);
}
