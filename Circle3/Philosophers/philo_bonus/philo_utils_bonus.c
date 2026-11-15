/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ucho <ucho@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 19:38:04 by ucho              #+#    #+#             */
/*   Updated: 2025/11/13 01:46:18 by ucho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

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

void	ft_semname(char *name, int num)
{
	char	*prefix;
	int		idx;

	memset(name, '0', 20);
	name[20] = '\0';
	prefix = "/stop_sem_";
	idx = -1;
	while (prefix[++idx])
		name[idx] = prefix[idx];
	idx = 19;
	while (num > 0 && idx >= 10)
	{
		name[idx--] = (num % 10) + '0';
		num /= 10;
	}
}
