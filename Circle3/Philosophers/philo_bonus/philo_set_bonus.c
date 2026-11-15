/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_set_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ucho <ucho@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 19:38:04 by ucho              #+#    #+#             */
/*   Updated: 2025/11/13 18:32:03 by ucho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	set_rule(int argc, char **argv, t_rule *rule);

void	set_philo(int argc, char **argv, t_rule *rule)
{
	set_rule(argc, argv, rule);
	del_sem(rule);
	if (!set_sem(&rule->fork_sem, FORK_SEM, rule->num_philo)
		|| !set_sem(&rule->util_sem[GATE], GATE_SEM, rule->num_philo / 2)
		|| !set_sem(&rule->util_sem[LOG], LOG_SEM, 1)
		|| !set_sem(&rule->util_sem[LOCK], LOCK_SEM, 1))
		rule->err = TRUE;
	if (rule->err)
	{
		let_sem(rule);
		del_sem(rule);
		exit(1);
	}
}

static void	set_rule(int argc, char **argv, t_rule *rule)
{
	memset(rule, 0, sizeof(t_rule));
	if (argc < 5 || argc > 6)
	{
		put_err("Error: invalid number of arguments\n");
		exit(1);
	}
	rule->num_philo = ft_atoll(argv[1]);
	rule->time_die = ft_atoll(argv[2]);
	rule->time_eat = ft_atoll(argv[3]);
	rule->time_slp = ft_atoll(argv[4]);
	rule->min_eat = NONE;
	if (argc == 6)
		rule->min_eat = ft_atoll(argv[5]);
	if (rule->num_philo == 0 || rule->num_philo == -1 || rule->time_die == -1
		|| rule->time_eat == -1 || rule->time_slp == -1 || rule->min_eat == -1
		|| rule->num_philo > INT_MAX || rule->time_die > INT_MAX
		|| rule->time_eat > INT_MAX || rule->time_slp > INT_MAX
		|| rule->min_eat > INT_MAX)
	{
		put_err("Error: invalid argument value\n");
		exit(1);
	}
}
