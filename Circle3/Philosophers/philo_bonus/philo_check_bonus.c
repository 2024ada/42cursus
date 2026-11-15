/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_check_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ucho <ucho@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 19:38:04 by ucho              #+#    #+#             */
/*   Updated: 2025/11/13 02:54:07 by ucho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	*check_death(void *param)
{
	t_info		*info;
	long long	last_eat;

	info = (t_info *)param;
	while (TRUE)
	{
		sem_wait(info->rule->util_sem[STOP]);
		last_eat = info->last_eat;
		if (info->rule->stop)
		{
			sem_post(info->rule->util_sem[STOP]);
			break ;
		}
		sem_post(info->rule->util_sem[STOP]);
		if (get_timediff(last_eat) >= info->rule->time_die)
			put_log(info, DIE);
		usleep(1000);
	}
	return (NULL);
}

int	check_stop(t_info *info)
{
	if (info->rule->min_eat != NONE && info->num_eat >= info->rule->min_eat)
	{
		sem_wait(info->rule->util_sem[STOP]);
		info->rule->stop = TRUE;
		sem_post(info->rule->util_sem[STOP]);
		return (TRUE);
	}
	return (FALSE);
}
