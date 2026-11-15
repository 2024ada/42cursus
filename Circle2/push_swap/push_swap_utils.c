/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ucho <ucho@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 20:53:12 by ucho              #+#    #+#             */
/*   Updated: 2025/05/08 02:39:50 by ucho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

char	*ft_strcjoin(char const *s1, char const *s2, char *charset)
{
	char	*str;
	size_t	len;

	if (!s1 || !s2)
		return (NULL);
	len = ft_strlen(s1) + ft_strlen(charset) + ft_strlen(s2);
	str = (char *)malloc(len + 1);
	if (!str)
		return (NULL);
	ft_strlcpy(str, s1, ft_strlen(s1) + 1);
	if (charset)
		ft_strlcpy(str + ft_strlen(s1), charset, ft_strlen(charset) + 1);
	ft_strlcpy(str + ft_strlen(s1) + ft_strlen(charset), s2, ft_strlen(s2) + 1);
	return (str);
}

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

int	get_min(int	*array, int size)
{
	int	min;
	int	i;

	min = 0;
	i = 1;
	while (i < size)
	{
		if (array[min] > array[i])
			min = i;
		i++;
	}
	return (min);
}

int	get_abs(int num)
{
	if (num < 0)
		return (-num);
	else
		return (num);
}

int	put_result(int is_ok)
{
	if (is_ok == TRUE)
	{
		write(1, "OK\n", 3);
		exit(0);
	}
	else if (is_ok == FALSE)
	{
		write(1, "KO\n", 3);
		exit(0);
	}
	else if (is_ok == ERROR)
	{
		write(2, "Error\n", 6);
		exit(1);
	}
	return (1);
}
