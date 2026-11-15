/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_run_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ucho <ucho@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 19:38:04 by ucho              #+#    #+#             */
/*   Updated: 2025/11/13 18:30:19 by ucho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	run_philo(t_rule *rule, t_info *info)
{
	memset(info, 0, sizeof(t_info));
	rule->philo = (pid_t *)malloc(sizeof(pid_t) * (size_t)rule->num_philo);
	if (!rule->philo)
	{
		put_err("Error: memory allocation failed\n");
		rule->err = TRUE;
	}
	rule->start = get_timestamp();
	info->last_eat = rule->start;
	info->rule = rule;
	if (!simulation(info))
		rule->err = TRUE;
	if (rule->err)
	{
		let_sem(rule);
		del_sem(rule);
		exit(1);
	}
}
