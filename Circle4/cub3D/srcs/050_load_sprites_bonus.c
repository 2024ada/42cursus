/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   055_load_sprites_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ucho <ucho@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/09 04:50:27 by ucho              #+#    #+#             */
/*   Updated: 2026/07/09 04:50:27 by ucho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D_bonus.h>

#ifdef BONUS

int	load_prop(t_app *app, t_game *game)
{
	t_idx	i;

	i = -1;
	while (++i < SLOT_COUNT)
	{
		if (game->asset.props[i].path)
		{
			if (load_xpm_image(app, game->asset.props[i].path,
					&game->asset.props[i].img))
				return (put_load_err((char []){i + 'A', 0},
					game->asset.props[i].path));
			game->runtime.prop_half[i]
				= get_prop_half(&game->asset.props[i].img);
		}
	}
	return (SUCCESS);
}

int	load_item(t_app *app, t_game *game)
{
	t_tex	*tex;
	t_idx	i;

	i = -1;
	while (++i < SLOT_COUNT)
	{
		tex = (t_tex *)vec_at(&game->asset.item_heal[i].vec, 0);
		if (tex)
			if (load_xpm_image(app, tex->path, &tex->img))
				return (put_load_err("I_H", tex->path));
		tex = (t_tex *)vec_at(&game->asset.item_gear[i].vec, 0);
		if (tex)
			if (load_xpm_image(app, tex->path, &tex->img))
				return (put_load_err("I_A", tex->path));
	}
	if (game->asset.item_goal.path)
		if (load_xpm_image(app, game->asset.item_goal.path,
				&game->asset.item_goal.img))
			return (put_load_err("I_M", game->asset.item_goal.path));
	return (SUCCESS);
}

int	load_mob(t_app *app, t_game *game)
{
	const char	*names[] = {"M_F", "M_B", "M_L", "M_R", "M_A", "M_D", NULL};
	t_tex		*tex;
	t_idx		i;
	t_idx		j;
	t_idx		k;

	i = -1;
	while (++i < SLOT_COUNT)
	{
		if (is_mob_complete(game, i))
		{
			j = -1;
			while (++j < MOB_COUNT)
			{
				k = -1;
				while (++k < game->asset.mobs[j][i].vec.len)
				{
					tex = (t_tex *)vec_at(&game->asset.mobs[j][i].vec, k);
					if (load_xpm_image(app, tex->path, &tex->img))
						return (put_load_err(names[j], tex->path));
				}
			}
		}
	}
	return (SUCCESS);
}

static int	get_door_pivot(t_img *tex)
{
	unsigned int	color;
	t_pos			x;
	t_pos			y;

	y = -1;
	while (++y < tex->size.h)
	{
		x = -1;
		while (++x < tex->size.w)
		{
			color = *(unsigned int *)(tex->addr
					+ y * tex->line_len + x * (tex->bpp / 8));
			if ((color & TRANSPARENT) != TRANSPARENT)
				return (y);
		}
	}
	return (0);
}

int	load_door(t_app *app, t_game *game)
{
	const char	*types[DOOR_COUNT]
		= {"D frame", "D slide", "D ceiling", "D left", "D right"};
	t_idx		i;
	t_idx		j;

	i = -1;
	while (++i < SLOT_COUNT)
	{
		if (game->asset.door[DOOR_FRAME][i].path)
		{
			j = -1;
			while (++j < DOOR_COUNT)
			{
				if (load_xpm_image(app, game->asset.door[j][i].path,
					&game->asset.door[j][i].img))
					return (put_load_err(types[j],
							game->asset.door[j][i].path));
			}
			get_door_jamb(&game->asset.door[DOOR_FRAME][i].img,
				&game->runtime.door_shape[i]);
			game->runtime.door_shape[i].pivot = get_door_pivot(
					&game->asset.door[DOOR_PANEL][i].img);
		}
	}
	return (SUCCESS);
}

#endif
