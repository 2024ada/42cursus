/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_c.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ucho <ucho@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 03:20:15 by ucho              #+#    #+#             */
/*   Updated: 2025/01/23 20:23:58 by ucho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	put_char(va_list args, int *bytes, t_flag *flag)
{
	char	c;
	int		size;
	int		span;

	c = (char)va_arg(args, int);
	size = 1;
	span = 0;
	if (flag->width > 0)
		span = flag->width - size;
	if (!flag->minus)
		put_space(span);
	write(STDOUT_FILENO, &c, size);
	if (flag->minus)
		put_space(span);
	(*bytes) += (span + 1);
}
