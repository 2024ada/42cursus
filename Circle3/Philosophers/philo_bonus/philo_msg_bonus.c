/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_msg_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ucho <ucho@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 19:38:04 by ucho              #+#    #+#             */
/*   Updated: 2025/11/13 03:01:57 by ucho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	put_err(const char *msg)
{
	write(2, msg, ft_strlen(msg));
	return (FALSE);
}

void	put_log(t_info *info, int state)
{
	const char	*msg[5] = {"has taken a fork", "is eating",
		"is sleeping", "is thinking", "died"};

	sem_wait(info->rule->util_sem[LOCK]);
	sem_wait(info->rule->util_sem[LOG]);
	printf("%lld %lld %s\n", get_timediff(info->rule->start),
		info->who + 1, msg[state]);
	if (state == DIE)
	{
		sem_post(info->rule->util_sem[LOG]);
		exit(1);
	}
	sem_post(info->rule->util_sem[LOG]);
	sem_post(info->rule->util_sem[LOCK]);
}
