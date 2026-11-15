/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   093_exec_mobs_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ucho <ucho@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/09 04:52:05 by ucho              #+#    #+#             */
/*   Updated: 2026/07/09 04:52:05 by ucho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D_bonus.h>

#ifdef BONUS

static double	update_mob_state(t_game *game, t_mob *mob)
{
	double	dist;
	double	dt;

	dist = 0.0;
	if (mob->last_update_time <= 0.0)
		mob->last_update_time = game->state.now;
	dt = game->state.now - mob->last_update_time;
	if (dt < 0.0 || dt > 0.2)
		dt = 0.016;
	mob->last_update_time = game->state.now;
	mob->anim.elapsed += dt;
	if (mob->anim.mode > MOB_DEAD && spot_hero(game, mob, &dist))
	{
		if (mob->anim.mode != MOB_SHOOT && mob->anim.mode != MOB_CHASE)
			mob->anim = (struct s_anim){0.0, 0.0, MOB_SHOOT};
	}
	else if (mob->anim.mode > MOB_PATROL)
	{
		mob->anim = (struct s_anim){0.0, 0.0, MOB_PATROL};
		if (fabs(mob->dir.x) >= fabs(mob->dir.y))
			mob->dir = (t_dxy){(mob->dir.x >= 0.0) - (mob->dir.x < 0.0), 0.0};
		else
			mob->dir = (t_dxy){0.0, (mob->dir.y >= 0.0) - (mob->dir.y < 0.0)};
	}
	return (dist);
}

void	exec_mobs(t_game *game)
{
	t_mob	*mob;
	double	dist;
	t_idx	i;

	i = -1;
	while (++i < game->entity.mobs.len)
	{
		mob = (t_mob *)vec_at(&game->entity.mobs, i);
		if (mob && mob->is_alive)
		{
			dist = update_mob_state(game, mob);
			if (mob->anim.mode == MOB_DEAD)
				exec_mob_death(game, mob);
			else if (mob->anim.mode == MOB_PAIN)
				exec_mob_pain(mob);
			else if (mob->anim.mode == MOB_SHOOT)
				exec_mob_attack(game, mob, dist);
			else if (mob->anim.mode == MOB_CHASE)
				exec_mob_chase(game, mob);
			else if (mob->anim.mode == MOB_PATROL)
				exec_mob_patrol(game, mob);
			if (game->state.hero_hp <= 0)
				break ;
		}
	}
}

#endif
