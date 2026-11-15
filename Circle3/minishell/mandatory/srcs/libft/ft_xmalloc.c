/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_xmalloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ucho <ucho@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 20:35:16 by ucho              #+#    #+#             */
/*   Updated: 2026/01/29 04:25:18 by ucho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_libft.h"

void	*ft_xmalloc(size_t size)
{
	void	*ptr;

	ptr = malloc(size);
	if (!ptr)
	{
		ft_putstr_fd("minishell: xmalloc: cannot allocate ", 2);
		ft_putnbr_fd(size, 2);
		ft_putstr_fd(" bytes\n", 2);
		exit(FAILURE);
	}
	return (ptr);
}
