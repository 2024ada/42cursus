/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lltoa_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ucho <ucho@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 11:14:30 by ucho              #+#    #+#             */
/*   Updated: 2026/01/29 04:22:36 by ucho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_libft_bonus.h"

static int	ft_numberlen(long long *divisor, long long nbr)
{
	long long	n;
	int			len;

	len = 1;
	n = nbr;
	if (nbr < 0)
	{
		len++;
		n = -n;
	}
	while (n / *divisor >= 10)
	{
		*divisor *= 10;
		len++;
	}
	return (len);
}

char	*ft_lltoa(long long n)
{
	char		*result;
	long long	divisor;
	long long	nbr;
	int			len;
	int			i;

	divisor = 1;
	len = ft_numberlen(&divisor, n);
	result = (char *)ft_xmalloc(len + 1);
	result[len] = '\0';
	nbr = n;
	if (nbr < 0)
	{
		nbr = -nbr;
		result[0] = '-';
	}
	i = len - 1;
	while (divisor > 0)
	{
		result[i--] = (nbr % 10) + '0';
		nbr /= 10;
		divisor /= 10;
	}
	return (result);
}
