/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   103_free_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ucho <ucho@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/09 04:52:27 by ucho              #+#    #+#             */
/*   Updated: 2026/07/09 04:52:28 by ucho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D_bonus.h>

#ifdef BONUS

static void	free_assets(t_app *app, t_game *game)
{
	t_idx	i;

	i = -1;
	while (++i < WALL_DIR_COUNT)
	{
		destroy_img(app->core.mlx, &game->asset.wall_base[i].img);
		free(game->asset.wall_base[i].path);
	}
	destroy_texture_vec(app, &game->asset.background[0].vec);
	destroy_texture_vec(app, &game->asset.background[1].vec);
	destroy_texture_vec(app, &game->asset.wall_deco.vec);
	destroy_texture_vec(app, &game->asset.hand_idle.vec);
	destroy_texture_vec(app, &game->asset.overlay_damage.vec);
	destroy_texture_vec(app, &game->asset.hud.vec);
	i = -1;
	while (++i < 26)
		destroy_texture_vec(app, &game->asset.hand_shot[i].vec);
	free(game->asset.wall_goal.path);
	destroy_img(app->core.mlx, &game->asset.wall_goal.img);
}

static void	free_sprites(t_app *app, t_game *game)
{
	t_idx	i;

	i = -1;
	while (++i < 26)
	{
		destroy_texture_vec(app, &game->asset.item_heal[i].vec);
		destroy_texture_vec(app, &game->asset.item_gear[i].vec);
		destroy_img(app->core.mlx, &game->asset.props[i].img);
		free(game->asset.props[i].path);
	}
	free(game->asset.item_goal.path);
	destroy_img(app->core.mlx, &game->asset.item_goal.img);
	vec_free(&game->entity.props);
	vec_free(&game->entity.items);
	vec_free(&game->entity.mobs);
	vec_free(&game->snapshot.entity.props);
	vec_free(&game->snapshot.entity.items);
	vec_free(&game->snapshot.entity.mobs);
}

static void	free_map(t_game *game)
{
	t_pos	y;

	y = 0;
	while (y < game->scene.map.size.h)
	{
		if (game->scene.map.grid)
			free(game->scene.map.grid[y]);
		if (game->scene.map.zone)
			free(game->scene.map.zone[y]);
		if (game->scene.map.deco)
			free(game->scene.map.deco[y]);
		if (game->scene.map.door)
			free(game->scene.map.door[y]);
		y++;
	}
	free(game->scene.map.zone);
	free(game->scene.map.deco);
	free(game->scene.map.door);
	free(game->scene.map.grid);
}

void	free_cub(t_app *app, t_game *game)
{
	free_assets(app, game);
	free_door(app, game);
	free_mob(app, game);
	free_sprites(app, game);
	free_map(game);
}

void	free_texs(t_tex tex[DOOR_COUNT][SLOT_COUNT],
	t_idx type, t_num count)
{
	while (count > 0)
	{
		count--;
		free(tex[count][type].path);
		tex[count][type].path = NULL;
	}
}

#endif
