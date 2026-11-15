/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_msg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ucho <ucho@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/09 00:00:00 by ucho              #+#    #+#             */
/*   Updated: 2025/11/13 01:45:35 by ucho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	put_err(const char *msg)
{
	write(2, msg, ft_strlen(msg));
	return (FALSE);
}

void	put_log(t_info *info, int state)
{
	const char	*msg[5] = {"has taken a fork", "is eating",
		"is sleeping", "is thinking", "died"};

	pthread_mutex_lock(&info->rule->util_mtx[LOG]);
	pthread_mutex_lock(&info->rule->util_mtx[STOP]);
	if (info->rule->stop)
	{
		pthread_mutex_unlock(&info->rule->util_mtx[STOP]);
		pthread_mutex_unlock(&info->rule->util_mtx[LOG]);
		return ;
	}
	if (state == DIE)
	{
		info->rule->stop = TRUE;
		printf("%lld %lld %s\n", get_timediff(info->rule->start),
			info->who + 1, msg[state]);
		pthread_mutex_unlock(&info->rule->util_mtx[STOP]);
		pthread_mutex_unlock(&info->rule->util_mtx[LOG]);
		return ;
	}
	printf("%lld %lld %s\n", get_timediff(info->rule->start),
		info->who + 1, msg[state]);
	pthread_mutex_unlock(&info->rule->util_mtx[STOP]);
	pthread_mutex_unlock(&info->rule->util_mtx[LOG]);
}
