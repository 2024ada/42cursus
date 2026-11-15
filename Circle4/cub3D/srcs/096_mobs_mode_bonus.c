/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   094_mobs_mode_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ucho <ucho@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/09 04:52:44 by ucho              #+#    #+#             */
/*   Updated: 2026/07/09 04:52:44 by ucho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D_bonus.h>

#ifdef BONUS

void	exec_mob_death(t_game *game, t_mob *mob)
{
	int	frame;

	frame = game->asset.mobs[MOB_DEATH][mob->type].vec.len - 1;
	if (mob->anim.frame < frame)
		mob->anim.frame = fmin(mob->anim.frame + 0.50, (double)frame);
	else
		mob->anim.frame = frame;
}

void	exec_mob_pain(t_mob *mob)
{
	if (mob->anim.elapsed >= MOB_PAIN_TIME
		&& mob->anim.mode != mob->pain_return_state)
	{
		mob->anim = (struct s_anim){0.0, 0.0, mob->pain_return_state};
		if (mob->pain_return_state == MOB_PATROL)
		{
			if (fabs(mob->dir.x) >= fabs(mob->dir.y))
				mob->dir
					= (t_dxy){(mob->dir.x >= 0.0) - (mob->dir.x < 0.0), 0.0};
			else
				mob->dir
					= (t_dxy){0.0, (mob->dir.y >= 0.0) - (mob->dir.y < 0.0)};
		}
	}
}

void	exec_mob_attack(t_game *game, t_mob *mob, double dist)
{
	t_num	count;

	set_mob_dir(mob, game->cam.pos);
	count = game->asset.mobs[MOB_ATTACK][mob->type].vec.len;
	if ((int)mob->anim.frame >= count)
	{
		if (game->state.hero_hp > 0
			&& dist <= MOB_ATTACK_RANGE
			&& !(mob->last_attack_time > 0.0
				&& game->state.now - mob->last_attack_time
				< MOB_COOL_TIME))
		{
			game->state.hero_hp -= mob->ap;
			game->state.hero_hp = max(game->state.hero_hp, 0);
			mob->last_attack_time = game->state.now;
			if (game->state.hero_hp > 0)
				game->hud.effect.hurt_until = game->state.now
					+ HERO_PAIN_TIME;
		}
		if (mob->anim.mode != MOB_CHASE)
			mob->anim = (struct s_anim){0.0, 0.0, MOB_CHASE};
	}
	mob->anim.frame += 0.20;
}

void	exec_mob_chase(t_game *game, t_mob *mob)
{
	set_mob_dir(mob, game->cam.pos);
	move_mob(game, mob, game->cam.pos);
	if (mob->anim.elapsed >= MOB_CHASE_TIME
		&& mob->anim.mode != MOB_SHOOT)
		mob->anim = (struct s_anim){0.0, 0.0, MOB_SHOOT};
	mob->anim.frame += 0.20;
}

void	exec_mob_patrol(t_game *game, t_mob *mob)
{
	t_dxy	next;

	next = (t_dxy){mob->pos.x + mob->dir.x * MOB_SPEED,
		mob->pos.y + mob->dir.y * MOB_SPEED};
	if (is_mob_blocked(game, next.x, mob->pos.y))
		mob->dir.x = -mob->dir.x;
	else
		mob->pos.x = next.x;
	if (is_mob_blocked(game, mob->pos.x, next.y))
		mob->dir.y = -mob->dir.y;
	else
		mob->pos.y = next.y;
	mob->anim.frame += 0.20;
}

#endif
