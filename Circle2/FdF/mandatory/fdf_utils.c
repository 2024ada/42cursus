/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ucho <ucho@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 15:11:17 by ucho              #+#    #+#             */
/*   Updated: 2025/08/19 16:39:45 by ucho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

long long	ft_atoll(const char *nptr)
{
	long long	sign;
	long long	digit;

	sign = 1;
	digit = 0;
	while ((9 <= *nptr && *nptr <= 13) || *nptr == 32)
		nptr++;
	if (*nptr == '-' || *nptr == '+')
	{
		if (*nptr == '-')
			sign *= -1;
		nptr++;
	}
	while ('0' <= *nptr && *nptr <= '9')
	{
		digit = (digit * 10) + (*nptr - '0');
		nptr++;
	}
	return (digit * sign);
}

int	put_error(const char *message)
{
	write(STDERR_FILENO, message, ft_strlen(message));
	return (0);
}
