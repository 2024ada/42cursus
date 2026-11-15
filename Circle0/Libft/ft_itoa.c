/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ucho <ucho@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 11:14:30 by ucho              #+#    #+#             */
/*   Updated: 2024/10/16 17:33:01 by ucho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static int	ft_numberlen(size_t *divisor, int nbr)
{
	size_t	n;
	int		len;

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

char	*ft_itoa(int n)
{
	char	*result;
	size_t	divisor;
	size_t	nbr;
	int		i;

	i = 0;
	divisor = 1;
	result = (char *)malloc(ft_numberlen(&divisor, n) + 1);
	if (!result)
		return (NULL);
	nbr = n;
	if (n < 0)
	{
		result[i++] = '-';
		nbr = -nbr;
	}
	while (divisor > 0)
	{
		result[i++] = (nbr / divisor) + '0';
		nbr %= divisor;
		divisor /= 10;
	}
	result[i] = '\0';
	return (result);
}
