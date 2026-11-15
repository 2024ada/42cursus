/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_let_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ucho <ucho@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 19:38:04 by ucho              #+#    #+#             */
/*   Updated: 2025/11/13 17:57:13 by ucho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static int	let_pid(pid_t *philo, t_info *info);

void	let_philo(t_info *info)
{
	if (!let_pid(info->rule->philo, info))
		info->rule->err = TRUE;
	let_sem(info->rule);
	del_sem(info->rule);
	if (info->rule->err)
		exit(1);
}

static int	let_pid(pid_t *philo, t_info *info)
{
	pid_t		died_philo;
	int			state;
	long long	idx;
	long long	cur;

	idx = -1;
	while (++idx < info->rule->num_philo)
	{
		died_philo = waitpid(-1, &state, 0);
		if (died_philo < 0)
			return (put_err("Error: waitpid failed\n"));
		if (WIFEXITED(state) && WEXITSTATUS(state) == 1)
		{
			cur = -1;
			while (++cur < info->rule->num_philo)
				if (philo[cur] != died_philo && philo[cur] > 0)
					kill(philo[cur], SIGKILL);
		}
	}
	return (TRUE);
}
