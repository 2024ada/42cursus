/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_token.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ucho <ucho@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 03:11:21 by ucho              #+#    #+#             */
/*   Updated: 2025/01/15 04:07:18 by ucho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	is_token(char token)
{
	char	*specifier;

	specifier = "cspdiuxX%\0";
	while (*specifier)
	{
		if (token == *specifier)
			return (TRUE);
		specifier++;
	}
	return (FALSE);
}

const char	*get_token(const char *text)
{
	while (*text == '-' || *text == '+'
		|| *text == '#' || *text == ' ' || *text == '0')
		text++;
	if (!*text)
		return (text);
	while ('0' <= *text && *text <= '9')
		text++;
	if (!*text)
		return (text);
	if (*text == '.')
		text++;
	if (!*text)
		return (text);
	while ('0' <= *text && *text <= '9')
		text++;
	if (!*text)
		return (text);
	return (text);
}

int	put_token(char token, va_list args, int *bytes, t_flag *flag)
{
	if (!flag)
		return (0);
	if (token == 'c')
		put_char(args, bytes, flag);
	else if (token == 's')
		put_string(args, bytes, flag);
	else if (token == 'p')
		put_pointer(args, bytes, flag);
	else if (token == 'd' || token == 'i')
		put_int(args, bytes, flag);
	else if (token == 'u')
		put_unsigned_int(args, bytes, flag);
	else if (token == 'x')
		put_hex(args, bytes, flag);
	else if (token == 'X')
	{
		flag->is_uppercase = 32;
		put_hex(args, bytes, flag);
	}
	else if (token == '%')
	{
		write(STDOUT_FILENO, "%", 1);
		(*bytes)++;
	}
	return (1);
}

void	put_space(int bytes)
{
	while (bytes)
	{
		write(STDOUT_FILENO, " ", 1);
		bytes--;
	}
}

char	*ft_strcpy(char *dest, const char *src)
{
	char	*ptr;

	ptr = dest;
	while (*src)
		*dest++ = *src++;
	*dest = '\0';
	return (ptr);
}
