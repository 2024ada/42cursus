/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ucho <ucho@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 15:42:46 by ucho              #+#    #+#             */
/*   Updated: 2025/11/13 01:45:46 by ucho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_isspace(char c);

long long	ft_atoll(const char *num)
{
	long long	sign;
	long long	digit;

	sign = -1;
	digit = 0;
	while (ft_isspace(*num))
		num++;
	if (*num == '+')
		num++;
	while ('0' <= *num && *num <= '9')
	{
		digit = (digit * 10) - (*num - '0');
		num++;
	}
	if (*num != '\0' && (*num < '0' || '9' < *num))
		return (-1);
	return (digit * sign);
}

size_t	ft_strlen(const char *str)
{
	size_t	len;

	len = 0;
	while (str[len])
		len++;
	return (len);
}

static int	ft_isspace(char c)
{
	if ((9 <= c && c <= 13) || c == 32)
		return (TRUE);
	return (FALSE);
}
