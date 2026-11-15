/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ucho <ucho@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 15:51:55 by ucho              #+#    #+#             */
/*   Updated: 2025/11/13 01:45:34 by ucho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_death(t_info *info)
{
	if (safe_read(&info->rule->util_mtx[STOP], &info->rule->stop))
		return (TRUE);
	if (get_timediff(info->last_eat) >= info->rule->time_die)
	{
		put_log(info, DIE);
		safe_write(&info->rule->util_mtx[STOP], &info->rule->stop, TRUE);
		return (TRUE);
	}
	return (FALSE);
}

int	check_stop(t_info *info)
{
	if (info->rule->min_eat != NONE && info->num_eat >= info->rule->min_eat)
	{
		pthread_mutex_lock(&info->rule->util_mtx[STOP]);
		info->rule->num_full++;
		if (info->rule->num_full >= info->rule->num_philo)
			info->rule->stop = TRUE;
		pthread_mutex_unlock(&info->rule->util_mtx[STOP]);
		return (TRUE);
	}
	return (FALSE);
}
