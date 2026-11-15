/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_sim_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ucho <ucho@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 19:38:04 by ucho              #+#    #+#             */
/*   Updated: 2025/11/13 18:31:49 by ucho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	multi_mode(t_info *info);
static int	take_fork(t_info *info);
static void	eating(t_info *info);

int	simulation(t_info *info)
{
	long long	idx;
	long long	cur;

	idx = -1;
	while (++idx < info->rule->num_philo)
	{
		info->who = idx;
		info->rule->philo[idx] = fork();
		if (info->rule->philo[idx] < 0)
		{
			cur = -1;
			while (++cur < idx)
				if (info->rule->philo[cur] > 0)
					kill(info->rule->philo[cur], SIGTERM);
			cur = -1;
			while (++cur < idx)
				if (info->rule->philo[cur] > 0)
					waitpid(info->rule->philo[cur], NULL, 0);
			return (put_err("Error: process fork failed\n"));
		}
		if (info->rule->philo[idx] == 0)
			multi_mode(info);
	}
	return (TRUE);
}

static void	multi_mode(t_info *info)
{
	pthread_t	checker;
	char		name[21];

	ft_semname(name, info->who);
	if (!set_sem(&info->rule->util_sem[STOP], name, 1))
		(let_sem(info->rule), \
		exit(1));
	if (pthread_create(&checker, NULL, check_death, (void *)info) != 0)
		(let_sem(info->rule), \
		exit(1));
	put_log(info, THINK);
	if ((info->who % 2) == 0)
		usleep(100 * info->rule->num_philo);
	while (!check_stop(info))
	{
		eating(info);
		put_log(info, SLEEP);
		if (check_stop(info))
			break ;
		ft_sleep(info->rule->time_slp);
		put_log(info, THINK);
	}
	pthread_join(checker, NULL);
	let_sem(info->rule);
	exit(0);
}

static int	take_fork(t_info *info)
{
	long long	last_eat;

	sem_wait(info->rule->util_sem[STOP]);
	last_eat = info->last_eat;
	sem_post(info->rule->util_sem[STOP]);
	if (last_eat == info->rule->start)
		return (FALSE);
	if (get_timediff(last_eat) >= info->rule->time_die - 10)
		return (FALSE);
	return (TRUE);
}

static void	eating(t_info *info)
{
	if (take_fork(info))
		ft_sleep(info->rule->time_slp);
	sem_wait(info->rule->util_sem[GATE]);
	sem_wait(info->rule->fork_sem);
	put_log(info, FORK);
	sem_wait(info->rule->fork_sem);
	put_log(info, FORK);
	put_log(info, EAT);
	sem_wait(info->rule->util_sem[STOP]);
	info->last_eat = get_timestamp();
	sem_post(info->rule->util_sem[STOP]);
	info->num_eat++;
	ft_sleep(info->rule->time_eat);
	sem_post(info->rule->fork_sem);
	sem_post(info->rule->fork_sem);
	sem_post(info->rule->util_sem[GATE]);
}
