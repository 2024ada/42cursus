/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ucho <ucho@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 21:50:07 by ucho              #+#    #+#             */
/*   Updated: 2025/11/13 01:45:48 by ucho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_info		*info;
	t_rule		rule;

	set_philo(argc, argv, &rule);
	run_philo(&rule, &info);
	let_philo(&rule, info);
	return (rule.err);
}
