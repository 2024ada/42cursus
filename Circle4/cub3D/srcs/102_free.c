/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   029_free.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ucho <ucho@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/09 04:49:11 by ucho              #+#    #+#             */
/*   Updated: 2026/07/09 04:49:11 by ucho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

#ifndef BONUS

void	free_cub(t_app *app, t_game *game)
{
	t_pos	y;
	t_idx	i;

	i = -1;
	while (++i < WALL_DIR_COUNT)
	{
		destroy_img(app->core.mlx, &game->asset.wall_base[i].img);
		free(game->asset.wall_base[i].path);
	}
	y = 0;
	while (y < game->scene.map.size.h)
	{
		if (game->scene.map.grid)
			free(game->scene.map.grid[y]);
		y++;
	}
	free(game->scene.map.grid);
}

void	destroy_app(t_app *app)
{
	t_idx	i;

	i = -1;
	while (++i < app->core.game_count)
		free_cub(app, &app->core.games[i]);
	destroy_mlx(&app->core);
}

#endif
