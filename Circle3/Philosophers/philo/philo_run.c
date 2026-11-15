/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_run.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ucho <ucho@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 15:48:38 by ucho              #+#    #+#             */
/*   Updated: 2025/11/13 17:43:01 by ucho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	set_info(t_rule *rule, t_info **info);

int	run_philo(t_rule *rule, t_info **info)
{
	memset(info, 0, sizeof(t_info *));
	if (rule->err)
		return (FALSE);
	rule->err = TRUE;
	if (!set_info(rule, info))
	{
		let_mtx(rule->fork_mtx, rule->num_philo);
		let_mtx(rule->util_mtx, 2);
		return (FALSE);
	}
	rule->philo = malloc(sizeof(pthread_t) * rule->num_philo);
	if (!rule->philo)
	{
		let_mtx(rule->fork_mtx, rule->num_philo);
		let_mtx(rule->util_mtx, 2);
		return (put_err("Error: memory allocation failed\n"));
	}
	if (!set_ths(rule, *info))
		return (FALSE);
	if (!let_ths(rule->philo, rule->num_philo))
		return (FALSE);
	rule->err = FALSE;
	return (TRUE);
}

static int	set_info(t_rule *rule, t_info **info)
{
	long long	idx;

	*info = malloc(sizeof(t_info) * rule->num_philo);
	if (!(*info))
		return (put_err("Error: memory allocation failed\n"));
	rule->start = get_timestamp();
	idx = -1;
	while (++idx < rule->num_philo)
	{
		(*info)[idx].who = idx;
		(*info)[idx].num_eat = 0;
		(*info)[idx].last_eat = rule->start;
		(*info)[idx].rule = rule;
	}
	return (TRUE);
}
