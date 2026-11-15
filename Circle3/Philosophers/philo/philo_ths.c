/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_ths.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ucho <ucho@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 15:46:18 by ucho              #+#    #+#             */
/*   Updated: 2025/11/13 17:26:13 by ucho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	set_ths(t_rule *rule, t_info *info)
{
	long long	idx;

	idx = -1;
	while (++idx < rule->num_philo)
	{
		if (pthread_create(&(rule->philo[idx]), \
			NULL, simulation, &(info)[idx]) != 0)
		{
			rule->stop = TRUE;
			let_ths(rule->philo, idx);
			let_mtx(rule->fork_mtx, rule->num_philo);
			let_mtx(rule->util_mtx, 2);
			return (put_err("Error: thread creation failed\n"));
		}
	}
	return (TRUE);
}

int	let_ths(pthread_t *philo, long long size)
{
	long long	idx;

	idx = -1;
	while (++idx < size)
		if (pthread_join(philo[idx], NULL) != 0)
			return (put_err("Error: thread join failed\n"));
	return (TRUE);
}
