/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_mtx.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ucho <ucho@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 15:46:26 by ucho              #+#    #+#             */
/*   Updated: 2025/11/13 17:21:11 by ucho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	set_mtx(t_rule *rule)
{
	long long	idx;

	idx = -1;
	while (++idx < rule->num_philo)
	{
		rule->fork[idx] = FALSE;
		if (pthread_mutex_init(&rule->fork_mtx[idx], NULL) != 0)
		{
			let_mtx(rule->fork_mtx, idx);
			return (put_err("Error: mutex initialization failed\n"));
		}
	}
	idx = -1;
	while (++idx < 2)
	{
		if (pthread_mutex_init(&rule->util_mtx[idx], NULL) != 0)
		{
			let_mtx(rule->fork_mtx, idx);
			let_mtx(rule->util_mtx, idx);
			return (put_err("Error: mutex initialization failed\n"));
		}
	}
	return (TRUE);
}

void	let_mtx(pthread_mutex_t *mtx, long long size)
{
	long long	idx;

	idx = -1;
	while (++idx < size)
		pthread_mutex_destroy(&mtx[idx]);
}

long long	safe_read(pthread_mutex_t *mtx, int *val)
{
	long long	ret;

	pthread_mutex_lock(mtx);
	ret = *val;
	pthread_mutex_unlock(mtx);
	return (ret);
}

void	safe_write(pthread_mutex_t *mtx, int *ret, int val)
{
	pthread_mutex_lock(mtx);
	*ret = val;
	pthread_mutex_unlock(mtx);
}
