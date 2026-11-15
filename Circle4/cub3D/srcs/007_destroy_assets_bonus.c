/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   102_destroy_assets_bonus.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ucho <ucho@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/09 04:52:25 by ucho              #+#    #+#             */
/*   Updated: 2026/07/09 04:52:26 by ucho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D_bonus.h>

#ifdef BONUS

static void	destroy_font(t_app *app);

void	free_door(t_app *app, t_game *game)
{
	t_door_shape	*shape;
	t_idx			i;
	t_idx			j;

	i = -1;
	while (++i < 26)
	{
		shape = &game->runtime.door_shape[i];
		j = -1;
		while (++j < DOOR_COUNT)
		{
			free(game->asset.door[j][i].path);
			destroy_image(app->core.mlx, &game->asset.door[j][i].img);
		}
		free(shape->jamb_left);
		free(shape->jamb_right);
		free(shape->jamb_head);
	}
}

void	free_mob(t_app *app, t_game *game)
{
	t_idx	i;
	t_idx	j;

	i = -1;
	while (++i < 26)
	{
		j = -1;
		while (++j < MOB_COUNT)
			destroy_texture_vec(app, &game->asset.mobs[j][i].vec);
	}
}

static void	destroy_screen(t_app *app)
{
	t_idx	i;

	free(app->rend.depth);
	app->rend.depth = NULL;
	destroy_font(app);
	destroy_image(app->core.mlx, &app->assets.outro_fail);
	destroy_image(app->core.mlx, &app->assets.outro_clear);
	destroy_image(app->core.mlx, &app->assets.outro_score);
	i = -1;
	while (++i < 4)
	{
		destroy_image(app->core.mlx, &app->assets.button[i][OFF]);
		destroy_image(app->core.mlx, &app->assets.button[i][ON]);
	}
	destroy_image(app->core.mlx, &app->assets.intro_title);
	destroy_image(app->core.mlx, &app->assets.intro_rules);
	i = -1;
	while (++i < PROL_COUNT)
		destroy_image(app->core.mlx, &app->assets.prologue[i]);
	destroy_image(app->core.mlx, &app->assets.mini_hero);
	destroy_image(app->core.mlx, &app->assets.mini_box);
}

static void	destroy_font(t_app *app)
{
	t_idx	i;

	i = -1;
	while (++i < FONT_COUNT)
		destroy_image(app->core.mlx, &app->assets.font[i]);
}

void	destroy_app(t_app *app)
{
	t_idx	i;

	destroy_screen(app);
	i = -1;
	while (++i < app->core.game_count)
		free_cub(app, &app->core.games[i]);
	destroy_mlx(&app->core);
}

#endif
