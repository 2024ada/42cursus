/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   065_init_mob_list_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ucho <ucho@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/09 04:50:51 by ucho              #+#    #+#             */
/*   Updated: 2026/07/09 04:50:51 by ucho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D_bonus.h>

#ifdef BONUS

static void	mix_mob_list(t_idx	*array, t_num count)
{
	int		temp;
	t_idx	pick;
	t_idx	i;

	i = count - 1;
	while (i > 0)
	{
		pick = ft_rand() % (i + 1);
		temp = array[i];
		array[i] = array[pick];
		array[pick] = temp;
		i--;
	}
}

static void	fill_mob_list(t_game *game, t_idx	*mob_map, t_num count)
{
	t_num	quotas[SLOT_COUNT];
	t_idx	type;
	t_idx	i;

	count_mob(game, quotas);
	i = 0;
	type = -1;
	while (++type < SLOT_COUNT)
	{
		while (quotas[type])
		{
			mob_map[i] = type;
			quotas[type]--;
			i++;
		}
	}
	mix_mob_list(mob_map, count);
}

static void	push_mob_list(t_game *game, t_idx type, size_t x, size_t y)
{
	t_mob	mob;
	t_idx	dir;

	ft_bzero(&mob, sizeof(t_mob));
	mob.type = type;
	mob.pos.x = x + 0.5;
	mob.pos.y = y + 0.5;
	mob.anim.mode = MOB_PATROL;
	mob.pain_return_state = MOB_PATROL;
	mob.is_alive = 1;
	mob.hp = MOB_HP;
	mob.ap = set_mob_ap(mob.type);
	mob.damage_resist = (double)set_hero_ap(mob.type)
		/ HERO_AP;
	dir = ft_rand() % 4;
	mob.dir.x = (dir == 0) - (dir == 1);
	mob.dir.y = (dir == 2) - (dir == 3);
	vec_push(&game->entity.mobs, &mob);
}

static void	set_mob_list(t_game *game, t_num num_mob)
{
	t_idx	*mob_map;
	t_idx	i;
	t_pos	x;
	t_pos	y;

	mob_map = ft_xmalloc(sizeof(int) * num_mob);
	fill_mob_list(game, mob_map, num_mob);
	i = 0;
	y = -1;
	while (++y < game->scene.map.size.h)
	{
		x = -1;
		while (++x < game->scene.map.size.w)
		{
			if (game->scene.map.grid[y][x] == 'M')
			{
				push_mob_list(game, mob_map[i++], x, y);
				game->scene.map.grid[y][x] = '0';
			}
		}
	}
	free(mob_map);
}

void	init_mob_list(t_game *game)
{
	t_num	num_mob;

	game->entity.mobs.len = 0;
	num_mob = count_tile(game, 'M');
	if (num_mob)
		set_mob_list(game, num_mob);
}

#endif
