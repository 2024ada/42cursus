/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ucho <ucho@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 11:14:11 by ucho              #+#    #+#             */
/*   Updated: 2026/01/29 04:26:29 by ucho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_libft.h"

static int	ft_isspace(char c)
{
	if ((9 <= c && c <= 13) || c == 32)
		return (TRUE);
	return (FALSE);
}

static int	is_sign(char c)
{
	if (c == '-')
		return (-1);
	else if (c == '+')
		return (1);
	return (FALSE);
}

int	ft_atoi(const char *nptr)
{
	int	sign;
	int	digit;

	sign = -1;
	digit = 0;
	while (ft_isspace(*nptr))
		nptr++;
	if (is_sign(*nptr) != FALSE)
	{
		if (is_sign(*nptr) == -1)
			sign *= -1;
		nptr++;
	}
	while ('0' <= *nptr && *nptr <= '9')
	{
		digit = (digit * 10) - (*nptr - '0');
		nptr++;
	}
	return (digit * sign);
}
