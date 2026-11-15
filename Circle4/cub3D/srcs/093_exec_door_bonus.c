/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   090_exec_door_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ucho <ucho@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/09 04:51:58 by ucho              #+#    #+#             */
/*   Updated: 2026/07/09 04:51:59 by ucho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D_bonus.h>

#ifdef BONUS

int	is_door_empty(t_game *game, t_pos map_x, t_pos map_y)
{
	t_box	door;
	t_box	actor;
	t_mob	*mob;
	t_idx	i;

	door = (t_box){{map_x + 0.5, map_y + 0.5}, {0.5, 0.5}};
	actor = (t_box){game->cam.pos, {HERO_MARGIN, HERO_MARGIN}};
	if (is_box_overlap(actor, door))
		return (FALSE);
	i = -1;
	while (++i < game->entity.mobs.len)
	{
		mob = (t_mob *)vec_at(&game->entity.mobs, i);
		if (mob && mob->is_alive && mob->anim.mode != MOB_DEAD)
		{
			actor = (t_box){mob->pos, {MOB_MARGIN, MOB_MARGIN}};
			if (is_box_overlap(actor, door))
				return (FALSE);
		}
	}
	return (TRUE);
}

static void	exec_door_tile(t_game *game, t_pos x, t_pos y)
{
	t_dmap	*door;

	door = &game->scene.map.door[y][x];
	if (door->progress < door->target)
	{
		door->progress = fmin(door->progress + 0.05, 1.0);
		if (door->progress == 1.0 && door->opened_at == 0.0)
			door->opened_at = game->state.now;
	}
	else if (door->progress > door->target)
	{
		if (!is_door_empty(game, x, y))
			*door = (t_dmap){door->progress, 0.0, TRUE};
		else
		{
			door->progress = fmax(door->progress - 0.05, 0.0);
			if (door->progress == 0.0)
				door->opened_at = 0.0;
		}
	}
	else if (door->target == TRUE
		&& door->progress == 1.0 && door->opened_at > 0.0
		&& get_now() - door->opened_at >= 3.0 && is_door_empty(game, x, y))
		*door = (t_dmap){door->progress, 0.0, FALSE};
}

void	exec_door(t_game *game)
{
	t_pos	x;
	t_pos	y;

	y = -1;
	while (++y < game->scene.map.size.h)
	{
		x = -1;
		while (++x < game->scene.map.size.w)
			exec_door_tile(game, x, y);
	}
}

#endif
