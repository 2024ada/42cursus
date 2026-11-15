/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   057_init_runtime_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ucho <ucho@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/09 04:50:33 by ucho              #+#    #+#             */
/*   Updated: 2026/07/09 04:50:33 by ucho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D_bonus.h>

#ifdef BONUS

static void	init_camera(t_game *game)
{
	game->cam.v_fov = 1.5;
	game->cam.pos.x = game->scene.pos.x + 0.5;
	game->cam.pos.y = game->scene.pos.y + 0.5;
	game->cam.dir.x = game->scene.dir.x;
	game->cam.dir.y = game->scene.dir.y;
	game->cam.plane.x = game->scene.plane.x;
	game->cam.plane.y = game->scene.plane.y;
	game->cam.eye_level = -400.0;
	game->cam.default_v_fov = game->cam.v_fov;
	game->cam.default_plane_len
		= sqrt(game->cam.plane.x * game->cam.plane.x
			+ game->cam.plane.y * game->cam.plane.y);
	if (game->cam.default_plane_len < 0.0001)
		game->cam.default_plane_len = 1.0;
}

static void	init_wall_deco(t_game *game)
{
	t_num	count;
	t_num	deco;
	t_pos	x;
	t_pos	y;

	if (!game->asset.wall_deco.vec.len)
		return ;
	game->scene.map.deco = ft_xmalloc(sizeof(int *) * game->scene.map.size.h);
	count = 0;
	y = -1;
	while (++y < game->scene.map.size.h)
	{
		game->scene.map.deco[y] = ft_xmalloc(sizeof(int)
				* game->scene.map.size.w);
		x = -1;
		while (++x < game->scene.map.size.w)
		{
			game->scene.map.deco[y][x] = -1;
			if (game->scene.map.grid[y][x] == '1')
				count++;
		}
	}
	deco = (int)(count * 0.40);
	if (deco)
		set_wall_deco(game, count, deco);
}

static void	init_door_anim(t_game *game)
{
	t_pos	y;

	game->scene.map.door
		= ft_xmalloc(sizeof(t_dmap *) * game->scene.map.size.h);
	y = -1;
	while (++y < game->scene.map.size.h)
	{
		game->scene.map.door[y]
			= ft_xmalloc(sizeof(t_dmap) * game->scene.map.size.w);
		ft_bzero(game->scene.map.door[y],
			sizeof(t_dmap) * game->scene.map.size.w);
	}
}

static void	init_prop_list(t_game *game)
{
	t_prop	prop;
	t_pos	x;
	t_pos	y;

	y = -1;
	while (++y < game->scene.map.size.h)
	{
		x = -1;
		while (++x < game->scene.map.size.w)
		{
			if (ft_strchr(optional_ids(), game->scene.map.grid[y][x]))
			{
				prop.pos.x = x + 0.5;
				prop.pos.y = y + 0.5;
				prop.type = game->scene.map.grid[y][x] - 'A';
				vec_push(&game->entity.props, &prop);
			}
		}
	}
}

void	init_runtime(t_app *app, t_game *game)
{
	reset_runtime(app, game);
	init_camera(game);
	init_wall_deco(game);
	init_door_anim(game);
	init_prop_list(game);
	init_item_goal(game);
	init_item_heal(game);
	init_item_gear(game);
	init_mob_list(game);
	game->state.hero_score = 0;
	game->state.hero_hp = HERO_HP;
	game->state.round_loaded = TRUE;
}

#endif
