/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_time_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ucho <ucho@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 19:38:04 by ucho              #+#    #+#             */
/*   Updated: 2025/11/13 01:46:17 by ucho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

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

int	ft_sleep(long long wait)
{
	long long	start;

	start = get_timestamp();
	while (get_timestamp() - start < wait)
		usleep(100);
	return (TRUE);
}
