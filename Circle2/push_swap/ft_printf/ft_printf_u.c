/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_u.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ucho <ucho@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 03:24:12 by ucho              #+#    #+#             */
/*   Updated: 2025/01/23 20:24:02 by ucho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	put_unsigned_int(va_list args, int *bytes, t_flag *flag)
{
	unsigned int	u;
	char			*s;
	long long		size;
	int				span;

	u = va_arg(args, int);
	size = ft_unsigned_intlen(u);
	span = filter_flag(0, &size, u, flag);
	s = get_unsigned_int(u, size);
	if (!flag->minus)
		put_space(span);
	write(STDOUT_FILENO, s, ft_strlen(s));
	if (flag->minus)
		put_space(span);
	(*bytes) += (ft_strlen(s) + span);
	free(s);
}

int	ft_unsigned_intlen(unsigned int nbr)
{
	unsigned int	n;
	unsigned int	divisor;
	int				bytes;

	divisor = 1;
	bytes = 1;
	n = nbr;
	while (n / divisor >= 10)
	{
		divisor *= 10;
		bytes++;
	}
	return (bytes);
}

char	*get_unsigned_int(unsigned int n, long long size)
{
	char			*result;
	unsigned int	nbr;
	long long		i;

	result = (char *)malloc(size + 1);
	if (!result)
		return (NULL);
	nbr = n;
	i = size;
	result[i--] = '\0';
	while (nbr > 0)
	{
		result[i--] = (nbr % 10) + '0';
		nbr /= 10;
	}
	while (i >= 0)
		result[i--] = '0';
	return (result);
}
