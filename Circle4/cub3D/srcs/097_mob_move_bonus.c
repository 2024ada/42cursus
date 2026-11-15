/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   100_mob_move_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ucho <ucho@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/09 04:52:19 by ucho              #+#    #+#             */
/*   Updated: 2026/07/09 04:52:20 by ucho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D_bonus.h>

#ifdef BONUS

int	is_mob_blocked(t_game *game, double x, double y)
{
	t_box	monster;
	t_box	player;

	monster = (t_box){{x, y}, {MOB_MARGIN, MOB_MARGIN}};
	if (overlap_wall(game, monster))
		return (TRUE);
	if (overlap_prop(game, monster))
		return (TRUE);
	player = (t_box){game->cam.pos, {HERO_MARGIN, HERO_MARGIN}};
	if (is_box_overlap(monster, player))
		return (TRUE);
	return (FALSE);
}

static int	spot_point(t_game *game, t_mob *mob, t_dxy point)
{
	t_dxy	delta;
	t_dxy	step;
	t_dxy	pos;
	double	dist;
	double	walked;

	delta = (t_dxy){point.x - mob->pos.x, point.y - mob->pos.y};
	dist = sqrt(delta.x * delta.x + delta.y * delta.y);
	if (dist < EPSILON)
		return (TRUE);
	if (dist > MOB_SIGHT || mob->dir.x * (delta.x / dist)
		+ mob->dir.y * (delta.y / dist) < MOB_ANGLE)
		return (FALSE);
	step = (t_dxy){delta.x / dist * RAY_STEP, delta.y / dist * RAY_STEP};
	pos = (t_dxy){mob->pos.x + step.x, mob->pos.y + step.y};
	walked = RAY_STEP;
	while (walked < dist)
	{
		if (overlap_wall(game, (t_box){pos, {EPSILON, EPSILON}})
			|| overlap_prop(game, (t_box){pos, {EPSILON, EPSILON}}))
			return (FALSE);
		pos = (t_dxy){pos.x + step.x, pos.y + step.y};
		walked += RAY_STEP;
	}
	return (TRUE);
}

int	spot_hero(t_game *game, t_mob *mob, double *dist)
{
	t_dxy	point[3];
	t_dxy	delta;
	t_dxy	side;
	t_idx	i;

	point[0] = game->cam.pos;
	point[1] = point[0];
	point[2] = point[0];
	delta = (t_dxy){game->cam.pos.x - mob->pos.x, game->cam.pos.y - mob->pos.y};
	*dist = sqrt(delta.x * delta.x + delta.y * delta.y);
	if (*dist >= EPSILON)
	{
		side = (t_dxy){(-(delta.y / *dist)), delta.x / *dist};
		point[1] = (t_dxy){point[0].x + side.x * HERO_MARGIN,
			point[0].y + side.y * HERO_MARGIN};
		point[2] = (t_dxy){point[0].x - side.x * HERO_MARGIN,
			point[0].y - side.y * HERO_MARGIN};
	}
	i = -1;
	while (++i < 3)
		if (spot_point(game, mob, point[i]))
			return (TRUE);
	return (FALSE);
}

int	set_mob_dir(t_mob *mob, t_dxy target)
{
	double	dist;

	dist = sqrt((target.x - mob->pos.x)
			* (target.x - mob->pos.x)
			+ (target.y - mob->pos.y)
			* (target.y - mob->pos.y));
	if (dist < 0.0001)
		return (FALSE);
	mob->dir.x = (target.x - mob->pos.x) / dist;
	mob->dir.y = (target.y - mob->pos.y) / dist;
	return (TRUE);
}

void	move_mob(t_game *game, t_mob *mob, t_dxy target)
{
	t_dxy	step;
	t_dxy	next;
	t_dxy	slide;

	if (!set_mob_dir(mob, target))
		return ;
	step = (t_dxy){mob->dir.x * MOB_SPEED,
		mob->dir.y * MOB_SPEED};
	if (fabs(step.x) > fabs(target.x - mob->pos.x))
		step.x = target.x - mob->pos.x;
	if (fabs(step.y) > fabs(target.y - mob->pos.y))
		step.y = target.y - mob->pos.y;
	next = (t_dxy){mob->pos.x + step.x, mob->pos.y + step.y};
	if (!is_mob_blocked(game, next.x, next.y))
		return ((void)(mob->pos = next));
	slide = (t_dxy){step.x * MOB_SLIDE, step.y * MOB_SLIDE};
	if (!is_mob_blocked(game, mob->pos.x + slide.x, mob->pos.y))
		mob->pos.x += slide.x;
	if (!is_mob_blocked(game, mob->pos.x, mob->pos.y + slide.y))
		mob->pos.y += slide.y;
}

#endif
