/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_let.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ucho <ucho@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 15:48:23 by ucho              #+#    #+#             */
/*   Updated: 2025/11/13 01:45:32 by ucho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	let_philo(t_rule *rule, t_info *info)
{
	if (!rule->err)
	{
		let_mtx(rule->fork_mtx, rule->num_philo);
		let_mtx(rule->util_mtx, 2);
	}
	free(rule->fork_mtx);
	free(rule->fork);
	free(rule->philo);
	free(info);
}
