/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   082_draw_minimap_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ucho <ucho@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/09 04:51:30 by ucho              #+#    #+#             */
/*   Updated: 2026/07/09 04:51:30 by ucho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D_bonus.h>

#ifdef BONUS

static char	get_minimap_tile(t_game *game, t_ixy pixel, t_rect rect)
{
	t_dxy	local;
	t_dxy	world;
	t_ixy	map;

	local.x = ((double)pixel.x - (rect.pos.x + rect.size.w / 2.0))
		/ (double)MINI_TILE;
	local.y = ((double)pixel.y - (rect.pos.y + rect.size.h / 2.0))
		/ (double)MINI_TILE;
	world.x = game->cam.pos.x - game->cam.dir.y * local.x
		- game->cam.dir.x * local.y;
	world.y = game->cam.pos.y + game->cam.dir.x * local.x
		- game->cam.dir.y * local.y;
	map.x = (int)floor(world.x);
	map.y = (int)floor(world.y);
	if (!is_in_map(game, map.x, map.y))
		return (' ');
	return (game->scene.map.grid[map.y][map.x]);
}

static void	draw_minimap_tile(t_app *app, t_game *game, t_rect rect)
{
	char	tile;
	int		color;
	t_ixy	pixel;

	pixel.y = rect.pos.y - 1;
	while (++pixel.y < rect.pos.y + rect.size.h)
	{
		pixel.x = rect.pos.x - 1;
		while (++pixel.x < rect.pos.x + rect.size.w)
		{
			tile = get_minimap_tile(game, pixel, rect);
			if (tile == '1'
				|| (tile == 'G' && game->state.num_goal < ITEM_GOAL_COUNT))
				color = MINI_WALL_COLOR;
			else if (tile == 'G')
				color = MINI_GOAL_COLOR;
			else if (is_door_sign(tile))
				color = MINI_DOOR_COLOR;
			else if (is_zone_sign(tile))
				color = MINI_FLOOR_COLOR;
			else
				color = MINI_EMPTY_COLOR;
			put_pixel(&app->core.screen, pixel, color);
		}
	}
}

static void	draw_minimap_hero(t_app *app, t_rect clip)
{
	t_rect	rect;
	t_rect	draw;
	t_dim	size;

	size = max((int)((double)MINI_TILE * MINI_HERO_SCALE), 4);
	rect.pos = (t_ixy){clip.pos.x + clip.size.w / 2 - size / 2,
		clip.pos.y + clip.size.h / 2 - size / 2};
	rect.size = (t_iwh){size, size};
	if (app->assets.mini_hero.img)
		draw_clipped_img(&app->core.screen, &app->assets.mini_hero,
			rect, clip);
	else
	{
		draw.pos.x = max(rect.pos.x, clip.pos.x);
		draw.pos.y = max(rect.pos.y, clip.pos.y);
		draw.size.w = min(rect.pos.x + rect.size.w,
				clip.pos.x + clip.size.w) - draw.pos.x;
		draw.size.h = min(rect.pos.y + rect.size.h,
				clip.pos.y + clip.size.h) - draw.pos.y;
		if (draw.size.w > 0 && draw.size.h > 0)
			draw_rect(app, draw, MINI_HERO_COLOR);
	}
}

void	draw_minimap(t_app *app, t_game *game)
{
	t_rect	rect;

	rect = (t_rect){(t_ixy){MINI_X, MINI_Y},
		(t_iwh){MINI_W, MINI_H}};
	draw_rect(app, rect, 0x00070A12);
	draw_minimap_tile(app, game, rect);
	draw_minimap_hero(app, rect);
	draw_scaled_img(&app->core.screen, &app->assets.mini_box, rect);
}

#endif
