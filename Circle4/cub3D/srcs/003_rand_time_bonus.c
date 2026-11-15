/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   038_rand_time_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ucho <ucho@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/09 04:49:39 by ucho              #+#    #+#             */
/*   Updated: 2026/07/09 04:49:39 by ucho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D_bonus.h>

#ifdef BONUS

int	ft_rand(void)
{
	static unsigned int	seed;
	struct timeval		tv;

	if (!seed)
	{
		gettimeofday(&tv, NULL);
		seed = (unsigned int)tv.tv_sec ^ (unsigned int)tv.tv_usec;
	}
	seed = seed * 1103515245 + 12345;
	return ((int)((seed / 65536) % 32768));
}

double	get_now(void)
{
	struct timeval	timeval;
	static double	last = 0.0;
	double			now;

	gettimeofday(&timeval, NULL);
	now = timeval.tv_sec + timeval.tv_usec * 0.000001;
	now = fmax(now, last);
	last = now;
	return (now);
}

#endif
