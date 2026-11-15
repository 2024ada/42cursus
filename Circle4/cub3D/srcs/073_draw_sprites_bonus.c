/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   077_draw_sprites_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ucho <ucho@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/09 04:51:18 by ucho              #+#    #+#             */
/*   Updated: 2026/07/09 04:51:19 by ucho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D_bonus.h>

#ifdef BONUS

static void	draw_mob_sprite(t_app *app, t_game *game, t_sprite sprite)
{
	t_mob	*mob;
	t_tex	*tex;
	double	bill[3];

	mob = (t_mob *)vec_at(&game->entity.mobs, sprite.i);
	bill[0] = mob->pos.x - game->cam.pos.x;
	bill[1] = mob->pos.y - game->cam.pos.y;
	bill[2] = 0.4;
	tex = get_mob_tile(game, mob);
	draw_billboard(app, game, tex, bill);
}

static void	draw_prop_sprite(t_app *app, t_game *game, t_sprite sprite)
{
	t_prop	*prop;
	t_tex	*tex;
	double	bill[3];

	prop = (t_prop *)vec_at(&game->entity.props, sprite.i);
	bill[0] = prop->pos.x - game->cam.pos.x;
	bill[1] = prop->pos.y - game->cam.pos.y;
	bill[2] = PROP_SCALE;
	tex = &game->asset.props[prop->type];
	draw_billboard(app, game, tex, bill);
}

static void	draw_item_sprite(t_app *app, t_game *game, t_sprite sprite,
	const double scales[3])
{
	t_item	*item;
	t_tex	*tex;
	double	bill[3];

	item = (t_item *)vec_at(&game->entity.items, sprite.i);
	bill[0] = item->pos.x - game->cam.pos.x;
	bill[1] = item->pos.y - game->cam.pos.y;
	bill[2] = scales[item->kind];
	if (item->kind == 0)
	{
		tex = &game->asset.item_goal;
		draw_billboard(app, game, tex, bill);
	}
	else if (item->kind == 1)
	{
		tex = (t_tex *)vec_at(&game->asset.item_heal[item->type].vec, 0);
		draw_billboard(app, game, tex, bill);
	}
	else if (item->kind == 2)
	{
		tex = (t_tex *)vec_at(&game->asset.item_gear[item->type].vec, 0);
		draw_billboard(app, game, tex, bill);
	}
}

void	draw_sprites(t_app *app, t_game *game)
{
	t_sprite		*sprites;
	t_num			count;
	t_idx			i;
	const double	scales[3]
		= {ITEM_GOAL_SCALE, ITEM_HEAL_SCALE, ITEM_GEAR_SCALE};

	sprites = (t_sprite *)ft_xmalloc(sizeof(t_sprite)
			* (game->entity.mobs.len + game->entity.props.len
				+ game->entity.items.len));
	count = 0;
	collect_mob_sprites(game, sprites, &count);
	collect_prop_sprites(game, sprites, &count);
	collect_item_sprites(game, sprites, &count);
	sort_sprites(sprites, count);
	i = -1;
	while (++i < count)
	{
		if (sprites[i].type == 0)
			draw_mob_sprite(app, game, sprites[i]);
		else if (sprites[i].type == 1)
			draw_prop_sprite(app, game, sprites[i]);
		else
			draw_item_sprite(app, game, sprites[i], scales);
	}
	free(sprites);
}

#endif
