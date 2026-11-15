/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_set.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ucho <ucho@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 15:47:27 by ucho              #+#    #+#             */
/*   Updated: 2025/11/13 17:37:06 by ucho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	set_rule(int argc, char **argv, t_rule *rule);

int	set_philo(int argc, char **argv, t_rule *rule)
{
	if (!set_rule(argc, argv, rule))
		return (FALSE);
	rule->err = TRUE;
	rule->fork = malloc(sizeof(long long) * rule->num_philo);
	if (!rule->fork)
		return (put_err("Error: memory allocation failed\n"));
	rule->fork_mtx = malloc(sizeof(pthread_mutex_t) * rule->num_philo);
	if (!rule->fork_mtx)
		return (put_err("Error: memory allocation failed\n"));
	if (!set_mtx(rule))
		return (FALSE);
	rule->err = FALSE;
	return (TRUE);
}

static int	set_rule(int argc, char **argv, t_rule *rule)
{
	memset(rule, 0, sizeof(t_rule));
	rule->err = TRUE;
	if (argc < 5 || argc > 6)
		return (put_err("Error: invalid number of arguments\n"));
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
		return (put_err("Error: invalid argument value\n"));
	rule->err = FALSE;
	return (TRUE);
}
