/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ucho <ucho@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 23:49:45 by ucho              #+#    #+#             */
/*   Updated: 2025/01/23 20:24:06 by ucho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printf(const char *format, ...)
{
	va_list		args;
	int			bytes;

	bytes = 0;
	va_start(args, format);
	put_format(format, args, &bytes);
	va_end(args);
	return (bytes);
}

void	put_format(const char *format, va_list args, int *bytes)
{
	int	err;

	err = FALSE;
	while (*format)
	{
		if (*format != INDICATOR)
		{
			write(STDOUT_FILENO, format, 1);
			(*bytes)++;
			format++;
			continue ;
		}
		format++;
		format = put_args(format, args, bytes, &err);
		if (format == NULL)
		{
			*bytes = -1;
			return ;
		}
		if (*format == '\0')
			return ;
	}
}

const char	*put_args(const char *format, va_list args, int *bytes, int *err)
{
	t_flag		*flag;
	const char	*token;

	flag = get_flag(format);
	if (!flag)
		return (NULL);
	token = get_token(format);
	while (*format && !is_token(*format))
		format++;
	if (token < format && !*err)
	{
		put_flag(bytes, flag);
		*err = TRUE;
	}
	else if (token == format && is_token(*token))
	{
		put_token(*token, args, bytes, flag);
		token++;
	}
	else if (*err)
		put_flag(bytes, flag);
	else
		*bytes = -1;
	free(flag);
	return (token);
}
