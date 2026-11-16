/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_p.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ucho <ucho@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 03:21:53 by ucho              #+#    #+#             */
/*   Updated: 2025/01/23 20:24:00 by ucho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	put_pointer(va_list args, int *len, t_flag *flag)
{
	void		*p;
	char		*s;
	long long	size;
	int			span;

	p = va_arg(args, void *);
	s = get_addr((unsigned long long)p, flag);
	if (!s)
		return ;
	size = ft_strlen(s);
	span = 0;
	if (flag->width > size)
		span = flag->width - size;
	if (!flag->minus)
		put_space(span);
	write(STDOUT_FILENO, s, size);
	if (flag->minus)
		put_space(span);
	(*len) += (size + span);
	free(s);
}

char	*get_addr(unsigned long long addr, t_flag *flag)
{
	char		*base;
	char		*result;
	long long	bytes;
	int			prefix;

	if (!addr)
		return (get_nil());
	base = "0123456789abcdef";
	bytes = ft_addrlen(addr, &prefix, flag);
	result = (char *)malloc(bytes + 1);
	if (!result)
		return (NULL);
	result[bytes--] = '\0';
	while (addr > 0)
	{
		result[bytes--] = base[addr % 16];
		addr /= 16;
	}
	while (prefix--)
		result[bytes--] = '0';
	result[bytes--] = 'x';
	result[bytes] = '0';
	if (flag->plus)
		result[0] = '+';
	return (result);
}

char	*get_nil(void)
{
	char	*result;

	result = (char *)malloc(6);
	if (!result)
		return (NULL);
	ft_strcpy(result, "(nil)");
	return (result);
}

int	ft_addrlen(unsigned long long p, int *prefix, t_flag *flag)
{
	unsigned long long	addr;
	unsigned long long	divisor;
	int					bytes;

	divisor = 1;
	bytes = 1;
	addr = p;
	while (addr / divisor >= 16)
	{
		divisor *= 16;
		bytes++;
	}
	(*prefix) = 0;
	if (flag->precision > bytes)
		(*prefix) = flag->precision - bytes;
	bytes += 2 + (*prefix) + flag->plus;
	return (bytes);
}
