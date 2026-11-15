/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ucho <ucho@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 22:05:42 by ucho              #+#    #+#             */
/*   Updated: 2025/11/13 01:45:49 by ucho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>

# define NONE -2

# define FORK 0
# define EAT 1
# define SLEEP 2
# define THINK 3
# define DIE 4

# define TRUE 1
# define FALSE 0

# define LOG 0
# define STOP 1

# define INT_MAX 2147483647

typedef struct timeval	t_time;

typedef struct s_rule
{
	long long		num_philo;
	long long		time_die;
	long long		time_eat;
	long long		time_slp;
	long long		min_eat;
	long long		num_full;
	long long		start;
	int				stop;
	int				err;
	pthread_t		*philo;
	int				*fork;
	pthread_mutex_t	*fork_mtx;
	pthread_mutex_t	util_mtx[2];
}	t_rule;

typedef struct s_info
{
	long long	who;
	long long	num_eat;
	long long	last_eat;
	t_rule		*rule;
}	t_info;

int			set_philo(int argc, char **argv, t_rule *rule);
int			run_philo(t_rule *rule, t_info **info);
void		let_philo(t_rule *rule, t_info *info);

void		*simulation(void *param);

int			let_ths(pthread_t *philo, long long count);
int			set_ths(t_rule *rule, t_info *info);

void		let_mtx(pthread_mutex_t *mtx, long long size);
int			set_mtx(t_rule *rule);
void		safe_write(pthread_mutex_t *mtx, int *ret, int val);
long long	safe_read(pthread_mutex_t *mtx, int *val);

long long	get_timestamp(void);
long long	get_timediff(long long start);
int			ft_sleep(t_info *info, long long wait);

int			check_death(t_info *info);
int			check_stop(t_info *info);

int			put_err(const char *msg);
void		put_log(t_info *info, int state);

long long	ft_atoll(const char *num);
size_t		ft_strlen(const char *str);

#endif
