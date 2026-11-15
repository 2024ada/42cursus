/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstrs_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ucho <ucho@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 11:31:51 by ucho              #+#    #+#             */
/*   Updated: 2026/01/29 04:25:50 by ucho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_libft.h"

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
