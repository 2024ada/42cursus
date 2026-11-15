/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_s.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ucho <ucho@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 03:21:56 by ucho              #+#    #+#             */
/*   Updated: 2025/01/23 20:24:01 by ucho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	put_string(va_list args, int *bytes, t_flag *flag)
{
	char	*s;
	int		size;
	int		span;

	s = va_arg(args, char *);
	if (s == NULL && flag->point && flag->precision < 6)
		s = "";
	else if (s == NULL)
		s = "(null)";
	size = ft_strlen(s);
	span = 0;
	if (flag->point)
	{
		if (flag->precision < size)
			size = flag->precision;
	}
	if (flag->width > size)
		span = flag->width - size;
	if (!flag->minus)
		put_space(span);
	write(STDOUT_FILENO, s, size);
	if (flag->minus)
		put_space(span);
	(*bytes) += (span + size);
}
