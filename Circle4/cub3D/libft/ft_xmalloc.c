/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_xmalloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ucho <ucho@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 20:35:16 by ucho              #+#    #+#             */
/*   Updated: 2026/07/08 13:23:03 by ucho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

void	*ft_xmalloc(size_t size)
{
	void	*ptr;

	ptr = malloc(size);
	if (!ptr)
	{
		ft_putendl_fd("Error", STDERR);
		ft_putstr_fd("[MEMORY] Cannot allocate ", STDERR);
		ft_putnbr_fd(size, STDERR);
		ft_putstr_fd(" bytes\n", STDERR);
		exit(FAILURE);
	}
	return (ptr);
}
