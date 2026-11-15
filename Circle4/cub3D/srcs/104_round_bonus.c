/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   104_round_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ucho <ucho@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/09 04:52:29 by ucho              #+#    #+#             */
/*   Updated: 2026/07/09 04:52:30 by ucho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D_bonus.h>

#ifdef BONUS

void	inherit_stat(t_game *prev, t_game *next)
{
	next->state.hero_hp = prev->state.hero_hp;
	next->state.hero_score = prev->state.hero_score;
	ft_memcpy(next->state.gear_charge, prev->state.gear_charge,
		sizeof(next->state.gear_charge));
}

#endif
