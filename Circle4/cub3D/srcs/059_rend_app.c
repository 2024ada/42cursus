/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   021_rend_app.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ucho <ucho@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/09 04:48:52 by ucho              #+#    #+#             */
/*   Updated: 2026/07/09 04:48:52 by ucho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

#ifndef BONUS

static void	draw_background(t_app *app, t_game *game)
{
	draw_rect(app,
		(t_rect){(t_ixy){0, 0}, (t_iwh){REND_W, REND_H / 2}},
		game->asset.rgb[CEIL]);
	draw_rect(app,
		(t_rect){(t_ixy){0, REND_H / 2},
		(t_iwh){REND_W, REND_H - REND_H / 2}},
		game->asset.rgb[FLOOR]);
}

static void	draw_walls(t_app *app, t_game *game)
{
	int		max;
	t_pos	x;

	max = game->scene.map.size.w + game->scene.map.size.h + 1;
	app->rend.hit.walls = ft_xmalloc(sizeof(t_face) * max);
	app->rend.hit.doors = NULL;
	x = -1;
	while (++x < REND_W)
		draw_wall(app, game, x);
	free(app->rend.hit.walls);
	app->rend.hit.walls = NULL;
}

#endif

void	draw_screen(t_app *app)
{
	unsigned int	color;
	t_pos			x;
	t_pos			y;

	y = -1;
	while (++y < WIN_H)
	{
		x = -1;
		while (++x < WIN_W)
		{
			color = get_scaled_pixel(&app->core.screen,
					(t_ixy){x, y}, WIN_W, WIN_H);
			put_pixel(&app->core.display, (t_ixy){x, y}, color);
		}
	}
}

void	draw_window(t_app *app)
{
	mlx_put_image_to_window(app->core.mlx,
		app->core.win, app->core.display.img, 0, 0);
}

#ifndef BONUS

void	rend_app(t_app *app, t_game *game)
{
	draw_background(app, game);
	draw_walls(app, game);
	draw_screen(app);
	draw_window(app);
}

#endif
