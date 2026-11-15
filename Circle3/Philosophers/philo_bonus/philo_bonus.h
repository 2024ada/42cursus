/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ucho <ucho@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 22:05:42 by ucho              #+#    #+#             */
/*   Updated: 2025/11/13 18:31:24 by ucho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <sys/time.h>
# include <sys/wait.h>
# include <signal.h>
# include <pthread.h>
# include <semaphore.h>
# include <fcntl.h>

# define NONE -2

# define FORK 0
# define EAT 1
# define SLEEP 2
# define THINK 3
# define DIE 4

# define TRUE 1
# define FALSE 0

# define FORK_SEM "/fork_sem"
# define GATE_SEM "/gate_sem"
# define LOG_SEM "/log_sem"
# define LOCK_SEM "/lock_sem"

# define GATE 0
# define LOG 1
# define LOCK 2
# define STOP 3

# define INT_MAX 2147483647

typedef struct timeval	t_time;

typedef struct s_rule
{
	long long	num_philo;
	long long	time_die;
	long long	time_eat;
	long long	time_slp;
	long long	min_eat;
	long long	start;
	int			stop;
	int			err;
	pid_t		*philo;
	sem_t		*fork_sem;
	sem_t		*util_sem[4];
}	t_rule;

typedef struct s_info
{
	long long	who;
	long long	num_eat;
	long long	last_eat;
	t_rule		*rule;
}	t_info;

void		set_philo(int argc, char **argv, t_rule *rule);
void		run_philo(t_rule *rule, t_info *info);
void		let_philo(t_info *info);

int			simulation(t_info *info);

int			set_sem(sem_t **sem, char *name, unsigned int val);
void		let_sem(t_rule *rule);
void		del_sem(t_rule *rule);

long long	get_timestamp(void);
long long	get_timediff(long long start);
int			ft_sleep(long long wait);

void		*check_death(void *param);
int			check_stop(t_info *info);

int			put_err(const char *msg);
void		put_log(t_info *info, int state);

long long	ft_atoll(const char *num);
size_t		ft_strlen(const char *str);
void		ft_semname(char *name, int num);

#endif