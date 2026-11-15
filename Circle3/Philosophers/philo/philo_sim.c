/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_sim.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ucho <ucho@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 15:52:29 by ucho              #+#    #+#             */
/*   Updated: 2025/11/13 02:05:35 by ucho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	*single_mode(t_info *info);
static int	multi_mode(t_info *info);
static int	take_fork(t_info *info, long long idx);
static int	eating(t_info *info, long long left, long long right);

void	*simulation(void *param)
{
	t_info	*info;

	info = (t_info *)param;
	if (info->rule->num_philo == 1)
		return (single_mode(info));
	if (!multi_mode(info))
		return (NULL);
	return (NULL);
}

static void	*single_mode(t_info *info)
{
	put_log(info, FORK);
	usleep(info->rule->time_die * 1000);
	put_log(info, DIE);
	return (NULL);
}

static int	multi_mode(t_info *info)
{
	long long	left;
	long long	right;

	left = info->who;
	right = (info->who + 1) % info->rule->num_philo;
	put_log(info, THINK);
	if ((info->who % 2) == 0)
		usleep(100 * info->rule->num_philo);
	while (!check_stop(info) && !check_death(info))
	{
		if (!eating(info, left, right))
			return (FALSE);
		put_log(info, SLEEP);
		if (check_stop(info))
			break ;
		if (check_death(info))
			break ;
		if (!ft_sleep(info, info->rule->time_slp))
			return (FALSE);
		put_log(info, THINK);
	}
	return (TRUE);
}

static int	take_fork(t_info *info, long long idx)
{
	while (!check_death(info))
	{
		if (safe_read(&info->rule->fork_mtx[idx],
				&info->rule->fork[idx]) == FALSE)
		{
			safe_write(&info->rule->fork_mtx[idx],
				&info->rule->fork[idx], TRUE);
			put_log(info, FORK);
			return (TRUE);
		}
		usleep(20);
	}
	return (FALSE);
}

static int	eating(t_info *info, long long left, long long right)
{
	if (!take_fork(info, left))
		return (FALSE);
	if (!take_fork(info, right))
	{
		safe_write(&info->rule->fork_mtx[left],
			&info->rule->fork[left], FALSE);
		return (FALSE);
	}
	put_log(info, EAT);
	info->last_eat = get_timestamp();
	info->num_eat++;
	if (!ft_sleep(info, info->rule->time_eat))
	{
		safe_write(&info->rule->fork_mtx[left],
			&info->rule->fork[left], FALSE);
		safe_write(&info->rule->fork_mtx[right],
			&info->rule->fork[right], FALSE);
		return (FALSE);
	}
	safe_write(&info->rule->fork_mtx[left],
		&info->rule->fork[left], FALSE);
	safe_write(&info->rule->fork_mtx[right],
		&info->rule->fork[right], FALSE);
	return (TRUE);
}
