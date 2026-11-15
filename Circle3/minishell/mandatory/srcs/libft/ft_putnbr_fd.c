/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ucho <ucho@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 11:31:59 by ucho              #+#    #+#             */
/*   Updated: 2026/01/29 04:25:52 by ucho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	int		number;
	int		divisor;
	char	output;

	if (n == -2147483648 && write(fd, "-2147483648", 11))
		return ;
	if (n < 0)
	{
		n = -n;
		write(fd, "-", 1);
	}
	number = n;
	divisor = 1;
	while (number / 10 > 0)
	{
		number /= 10;
		divisor *= 10;
	}
	while (divisor > 0)
	{
		output = (n / divisor) + '0';
		n %= divisor;
		write(fd, &output, 1);
		divisor /= 10;
	}
}
