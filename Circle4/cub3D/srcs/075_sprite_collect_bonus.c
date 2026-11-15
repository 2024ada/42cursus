/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   079_sprite_collect_bonus.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ucho <ucho@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/09 04:51:23 by ucho              #+#    #+#             */
/*   Updated: 2026/07/09 04:51:23 by ucho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D_bonus.h>

#ifdef BONUS

void	sort_sprites(t_sprite *sprites, t_num count)
{
	t_sprite	tmp;
	t_idx		i;
	t_idx		j;

	i = -1;
	while (++i < count - 1)
	{
		j = i;
		while (++j < count)
		{
			if (sprites[i].dist < sprites[j].dist)
			{
				tmp = sprites[i];
				sprites[i] = sprites[j];
				sprites[j] = tmp;
			}
		}
	}
}

void	collect_mob_sprites(t_game *game,
	t_sprite *sprites, t_num *count)
{
	t_mob	*mob;
	t_idx	i;

	i = -1;
	while (++i < game->entity.mobs.len)
	{
		mob = (t_mob *)vec_at(&game->entity.mobs, i);
		if (mob && mob->is_alive)
		{
			sprites[*count].i = i;
			sprites[*count].type = 0;
			sprites[*count].dist = (game->cam.pos.x - mob->pos.x)
				* (game->cam.pos.x - mob->pos.x)
				+ (game->cam.pos.y - mob->pos.y)
				* (game->cam.pos.y - mob->pos.y);
			(*count)++;
		}
	}
}

void	collect_prop_sprites(t_game *game,
	t_sprite *sprites, t_num *count)
{
	t_prop	*prop;
	t_idx	i;

	i = -1;
	while (++i < game->entity.props.len)
	{
		prop = (t_prop *)vec_at(&game->entity.props, i);
		sprites[*count].i = i;
		sprites[*count].type = 1;
		sprites[*count].dist = (game->cam.pos.x - prop->pos.x)
			* (game->cam.pos.x - prop->pos.x)
			+ (game->cam.pos.y - prop->pos.y)
			* (game->cam.pos.y - prop->pos.y);
		(*count)++;
	}
}

void	collect_item_sprites(t_game *game,
	t_sprite *sprites, t_num *count)
{
	t_item	*item;
	t_idx	i;

	i = -1;
	while (++i < game->entity.items.len)
	{
		item = (t_item *)vec_at(&game->entity.items, i);
		if (item->is_active)
		{
			sprites[*count].i = i;
			sprites[*count].type = 2;
			sprites[*count].dist = (game->cam.pos.x - item->pos.x)
				* (game->cam.pos.x - item->pos.x)
				+ (game->cam.pos.y - item->pos.y)
				* (game->cam.pos.y - item->pos.y);
			(*count)++;
		}
	}
}

#endif
