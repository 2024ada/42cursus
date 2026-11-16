/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ucho <ucho@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 03:18:43 by ucho              #+#    #+#             */
/*   Updated: 2025/01/23 20:23:57 by ucho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

t_flag	*get_flag(const char *format)
{
	t_flag	*flag;

	flag = set_flag();
	if (!flag)
		return (NULL);
	parse_flag(flag, &format);
	if (!parse_width(flag, &format))
		return (NULL);
	if (!parse_precision(flag, &format))
		return (NULL);
	return (flag);
}

t_flag	*set_flag(void)
{
	t_flag	*flag;

	flag = (t_flag *)malloc(sizeof(t_flag));
	if (!flag)
		return (NULL);
	flag->minus = 0;
	flag->plus = 0;
	flag->zero = 0;
	flag->sharp = 0;
	flag->space = 0;
	flag->width = 0;
	flag->point = 0;
	flag->precision = 0;
	flag->is_uppercase = 0;
	return (flag);
}

void	parse_flag(t_flag *flag, const char **format)
{
	while (**format == '+' || **format == '-'
		|| **format == '0' || **format == ' ' || **format == '#')
	{
		if (**format == '-')
			flag->minus = 1;
		if (**format == '+')
			flag->plus = 1;
		if (**format == '0')
			flag->zero = 1;
		if (**format == '#')
			flag->sharp = 1;
		if (**format == ' ')
			flag->space = 1;
		(*format)++;
	}
}

int	parse_width(t_flag *flag, const char **format)
{
	size_t	width;

	if ('0' <= **format && **format <= '9')
	{
		width = (size_t)(ft_atoi(*format));
		if (INT_MAX < width)
			return (0);
		flag->width = (int)width;
		while ('0' <= **format && **format <= '9')
			(*format)++;
	}
	return (1);
}

int	parse_precision(t_flag *flag, const char **format)
{
	size_t	precision;

	if (**format == '.')
	{
		flag->point = 1;
		(*format)++;
		if ('0' <= **format && **format <= '9')
		{
			precision = (size_t)(ft_atoi(*format));
			if (INT_MAX < precision)
				return (0);
			flag->precision = (int)precision;
			while ('0' <= **format && **format <= '9')
				(*format)++;
		}
	}
	return (1);
}
