/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_time.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ucho <ucho@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 15:50:15 by ucho              #+#    #+#             */
/*   Updated: 2025/11/13 01:45:45 by ucho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	get_timestamp(void)
{
	t_time	now;

	if (gettimeofday(&now, NULL) == -1)
		return (-1);
	return ((long long)now.tv_sec * 1000LL + (long long)now.tv_usec / 1000LL);
}

long long	get_timediff(long long start)
{
	long long	now;

	now = get_timestamp();
	if (now < 0)
		return (0);
	if (now < start)
		return (0);
	return (now - start);
}

int	ft_sleep(t_info *info, long long wait)
{
	long long	start;

	start = get_timestamp();
	while (get_timestamp() - start < wait)
	{
		if (check_death(info))
			return (FALSE);
		usleep(20);
	}
	return (TRUE);
}
