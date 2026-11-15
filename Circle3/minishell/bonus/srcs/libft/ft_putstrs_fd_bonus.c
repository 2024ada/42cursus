/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstrs_fd_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ucho <ucho@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 11:31:51 by ucho              #+#    #+#             */
/*   Updated: 2026/01/29 04:22:00 by ucho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_libft_bonus.h"

void	ft_putstrs_fd(char **strs, int fd)
{
	if (strs)
	{
		while (*strs)
		{
			ft_putstr_fd(*strs, fd);
			strs++;
		}
	}
}
