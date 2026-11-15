/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_sem_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ucho <ucho@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 19:38:04 by ucho              #+#    #+#             */
/*   Updated: 2025/11/13 18:31:32 by ucho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	set_sem(sem_t **sem, char *name, unsigned int val)
{
	*sem = sem_open(name, O_CREAT | O_EXCL, 0644, val);
	if (*sem == SEM_FAILED)
	{
		put_err("Error: semaphore open failed\n");
		return (FALSE);
	}
	return (TRUE);
}

void	let_sem(t_rule *rule)
{
	if (rule->fork_sem && rule->fork_sem != SEM_FAILED)
		sem_close(rule->fork_sem);
	if (rule->util_sem[GATE] && rule->util_sem[GATE] != SEM_FAILED)
		sem_close(rule->util_sem[GATE]);
	if (rule->util_sem[LOG] && rule->util_sem[LOG] != SEM_FAILED)
		sem_close(rule->util_sem[LOG]);
	if (rule->util_sem[LOCK] && rule->util_sem[LOCK] != SEM_FAILED)
		sem_close(rule->util_sem[LOCK]);
	if (rule->util_sem[STOP] && rule->util_sem[STOP] != SEM_FAILED)
		sem_close(rule->util_sem[STOP]);
	free(rule->philo);
}

void	del_sem(t_rule *rule)
{
	char		name[21];
	long long	idx;

	idx = -1;
	while (++idx < rule->num_philo)
	{
		ft_semname(name, idx);
		sem_unlink(name);
	}
	sem_unlink(FORK_SEM);
	sem_unlink(GATE_SEM);
	sem_unlink(LOG_SEM);
	sem_unlink(LOCK_SEM);
}
