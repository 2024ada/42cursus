/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ucho <ucho@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 11:14:14 by ucho              #+#    #+#             */
/*   Updated: 2026/01/29 04:22:49 by ucho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_libft_bonus.h"

void	ft_bzero(void *s, size_t n)
{
	unsigned char	*buffer;

	buffer = (unsigned char *)s;
	while (n)
	{
		*buffer = 0;
		buffer++;
		n--;
	}
}
