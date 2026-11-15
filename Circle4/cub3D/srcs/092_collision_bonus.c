/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   099_collision_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ucho <ucho@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/09 04:52:16 by ucho              #+#    #+#             */
/*   Updated: 2026/07/09 04:52:17 by ucho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D_bonus.h>

#ifdef BONUS

int	overlap_wall(t_game *game, t_box actor)
{
	t_box	door[2];
	t_box	box;
	t_ixy	tile;

	tile.y = (int)floor(actor.center.y - actor.half.y) - 1;
	while (++tile.y <= (int)floor(actor.center.y + actor.half.y))
	{
		tile.x = (int)floor(actor.center.x - actor.half.x) - 1;
		while (++tile.x <= (int)floor(actor.center.x + actor.half.x))
		{
			if (!is_walkable_tile(game, tile))
			{
				box = (t_box){{tile.x + 0.5, tile.y + 0.5}, {0.5, 0.5}};
				if (is_box_overlap(actor, box))
					return (TRUE);
			}
			if (get_jamb_box(game, tile, door)
				&& (is_box_overlap(actor, door[0])
					|| is_box_overlap(actor, door[1])))
				return (TRUE);
		}
	}
	return (FALSE);
}

static int	get_prop_box(t_game *game, t_prop *prop, t_box *box)
{
	double	half;

	if (!box || !prop || prop->type < 0 || prop->type >= SLOT_COUNT)
		return (FALSE);
	half = game->runtime.prop_half[prop->type];
	if (half <= EPSILON)
		return (FALSE);
	*box = (t_box){prop->pos, {half, half}};
	return (TRUE);
}

int	overlap_prop(t_game *game, t_box actor)
{
	t_prop	*prop;
	t_box	box;
	t_idx	i;

	i = -1;
	while (++i < game->entity.props.len)
	{
		prop = (t_prop *)vec_at(&game->entity.props, i);
		if (get_prop_box(game, prop, &box)
			&& is_box_overlap(actor, box))
			return (TRUE);
	}
	return (FALSE);
}

static int	overlap_mobs(t_game *game, t_box player)
{
	t_mob	*mob;
	t_box	box;
	t_idx	i;

	i = -1;
	while (++i < game->entity.mobs.len)
	{
		mob = (t_mob *)vec_at(&game->entity.mobs, i);
		if (mob && mob->is_alive && mob->anim.mode != MOB_DEAD)
		{
			box = (t_box){mob->pos, {MOB_MARGIN, MOB_MARGIN}};
			if (is_box_overlap(player, box))
				return (TRUE);
		}
	}
	return (FALSE);
}

int	is_hero_blocked(t_game *game, double x, double y)
{
	t_box	player;

	player = (t_box){{x, y}, {HERO_MARGIN, HERO_MARGIN}};
	if (overlap_wall(game, player))
		return (TRUE);
	if (overlap_prop(game, player))
		return (TRUE);
	if (overlap_mobs(game, player))
		return (TRUE);
	return (FALSE);
}

#endif
