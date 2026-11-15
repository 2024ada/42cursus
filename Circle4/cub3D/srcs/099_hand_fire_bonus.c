/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   096_hand_fire_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ucho <ucho@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/09 04:52:09 by ucho              #+#    #+#             */
/*   Updated: 2026/07/09 04:52:10 by ucho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D_bonus.h>

#ifdef BONUS

static int	is_blocked(t_game *game, t_dxy pos)
{
	t_ixy	map;
	t_box	point;

	map = (t_ixy){(int)pos.x, (int)pos.y};
	if (map.x < 0 || map.y < 0 || map.y >= game->scene.map.size.h
		|| game->scene.map.grid[map.y] == NULL
		|| map.x >= game->scene.map.size.w)
		return (1);
	if (game->scene.map.grid[map.y][map.x] == ' ')
		return (1);
	point = (t_box){pos, {EPSILON, EPSILON}};
	if (overlap_wall(game, point))
		return (1);
	if (overlap_prop(game, point))
		return (1);
	return (0);
}

static int	is_attack_valid(t_game *game, t_mob *mob, double dist)
{
	t_dxy	pos;
	t_dxy	step;
	double	walked;

	if (dist < EPSILON)
		return (0);
	step.x = (mob->pos.x - game->cam.pos.x) / dist * RAY_STEP;
	step.y = (mob->pos.y - game->cam.pos.y) / dist * RAY_STEP;
	pos.x = game->cam.pos.x + step.x;
	pos.y = game->cam.pos.y + step.y;
	walked = RAY_STEP;
	while (walked < dist)
	{
		if (is_blocked(game, pos))
			return (1);
		pos.x += step.x;
		pos.y += step.y;
		walked += RAY_STEP;
	}
	return (0);
}

static t_bool	is_target(t_game *game, t_mob *mob,
	double *best_dist, double *dot)
{
	t_dxy	delta;
	double	dist;

	delta.x = mob->pos.x - game->cam.pos.x;
	delta.y = mob->pos.y - game->cam.pos.y;
	dist = sqrt(delta.x * delta.x + delta.y * delta.y);
	if (dist > EPSILON && dist <= HERO_SIGHT)
	{
		*dot = game->cam.dir.x * (delta.x / dist)
			+ game->cam.dir.y * (delta.y / dist);
		if (*dot >= HERO_ANGLE && dist < *best_dist
			&& !is_attack_valid(game, mob, dist))
		{
			*best_dist = dist;
			return (TRUE);
		}
	}
	return (FALSE);
}

static t_mob	*find_target(t_game *game, double *best_dist, double *dot)
{
	t_mob	*mob;
	t_mob	*best;
	t_idx	i;

	best = NULL;
	*best_dist = HERO_SIGHT + 1.0;
	i = -1;
	while (++i < game->entity.mobs.len)
	{
		mob = (t_mob *)vec_at(&game->entity.mobs, i);
		if (mob && mob->is_alive && mob->anim.mode != MOB_DEAD
			&& is_target(game, mob, best_dist, dot))
			best = mob;
	}
	return (best);
}

void	run_hand_fire(t_game *game)
{
	t_mob	*mob;
	double	dist;
	double	dot;
	t_num	damage;

	mob = find_target(game, &dist, &dot);
	if (!mob)
		return ;
	damage = get_hero_ap(mob, dist, dot);
	mob->hp = max(mob->hp - damage, 0);
	face_mob_to_hero(game, mob);
	mob->anim.mode = MOB_PAIN;
	mob->anim.elapsed = 0.0;
	mob->anim.frame = 0.0;
	if (mob->hp == 0)
	{
		mob->anim.mode = MOB_DEAD;
		game->state.hero_score += SCORE + mob->type * 50;
	}
	else
		mob->pain_return_state = MOB_CHASE;
}

#endif
