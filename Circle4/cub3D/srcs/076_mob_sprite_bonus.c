/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   080_mob_sprite_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ucho <ucho@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/09 04:51:24 by ucho              #+#    #+#             */
/*   Updated: 2026/07/09 04:51:25 by ucho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D_bonus.h>

#ifdef BONUS

static t_vec	*get_mob_vec(t_game *game, t_mob *mob)
{
	double	angle;

	if (mob->anim.mode == MOB_SHOOT)
		return (&game->asset.mobs[MOB_ATTACK][mob->type].vec);
	if (mob->anim.mode == MOB_PAIN || mob->anim.mode == MOB_DEAD)
		return (&game->asset.mobs[MOB_DEATH][mob->type].vec);
	angle = atan2(mob->dir.y, mob->dir.x)
		- atan2(game->cam.pos.y - mob->pos.y,
			game->cam.pos.x - mob->pos.x);
	while (angle > PI)
		angle -= 2 * PI;
	while (angle < -PI)
		angle += 2 * PI;
	if (angle >= -PI / 4.0 && angle <= PI / 4.0)
		return (&game->asset.mobs[MOB_FRONT][mob->type].vec);
	if (angle > PI / 4.0 && angle <= 3.0 * PI / 4.0)
		return (&game->asset.mobs[MOB_LEFT][mob->type].vec);
	if (angle < -PI / 4.0 && angle >= -3.0 * PI / 4.0)
		return (&game->asset.mobs[MOB_RIGHT][mob->type].vec);
	return (&game->asset.mobs[MOB_BACK][mob->type].vec);
}

t_tex	*get_mob_tile(t_game *game, t_mob *mob)
{
	t_vec	*vec;
	t_idx	frame;

	vec = get_mob_vec(game, mob);
	frame = ((int)mob->anim.frame) % vec->len;
	if (mob->anim.mode == MOB_PAIN)
		frame = 0;
	else if (mob->anim.mode == MOB_SHOOT || mob->anim.mode == MOB_DEAD)
		frame = min((int)mob->anim.frame, vec->len - 1);
	return ((t_tex *)vec_at(vec, frame));
}

#endif
