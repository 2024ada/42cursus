/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_pid.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ucho <ucho@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 02:35:42 by ada               #+#    #+#             */
/*   Updated: 2025/05/27 15:12:35 by ucho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	put_info(char *program)
{
	program += 2;
	ft_putstr_fd(program, 2);
	ft_putstr_fd(": ", 2);
}

void	set_pid(t_info *info)
{
	int	i;

	info->pid = malloc(sizeof(pid_t) * info->size);
	if (!info->pid)
		exit(1);
	i = 0;
	while (i < info->size)
		info->pid[i++] = -1;
}
