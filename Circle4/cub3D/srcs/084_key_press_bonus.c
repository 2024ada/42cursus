/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   087_key_press_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ucho <ucho@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/09 04:51:51 by ucho              #+#    #+#             */
/*   Updated: 2026/07/09 04:51:52 by ucho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D_bonus.h>

#ifdef BONUS

static int	check_portal_tile(t_app *app, t_game *game, t_ixy map)
{
	char	tile;

	if (!is_in_map(game, map.x, map.y))
		return (TRUE);
	tile = game->scene.map.grid[map.y][map.x];
	if (is_door_sign(tile))
	{
		if (!game->scene.map.door[map.y][map.x].target
			|| is_door_empty(game, map.x, map.y))
			game->scene.map.door[map.y][map.x].target ^= 1;
		return (TRUE);
	}
	if (tile == 'G')
	{
		if (game->state.num_goal >= ITEM_GOAL_COUNT
			&& app->screen.dissolve.mode == GAME)
		{
			app->screen.dissolve.mode = DISSOLVE_CLEAR;
			if (app->core.curr_game + 1 < app->core.game_count)
				app->screen.dissolve.mode = FADEOUT_GOAL;
			app->screen.dissolve.started_at = game->state.now;
		}
		return (TRUE);
	}
	return (tile == '1');
}

static void	set_portal_ray(t_game *game,
	t_ixy *map, t_dxy *dist, t_ixy *step)
{
	*map = (t_ixy){(int)game->cam.pos.x, (int)game->cam.pos.y};
	dist[1].x = 1e30;
	dist[1].y = 1e30;
	if (game->cam.dir.x)
		dist[1].x = fabs(1.0 / game->cam.dir.x);
	if (game->cam.dir.y)
		dist[1].y = fabs(1.0 / game->cam.dir.y);
	step->x = (game->cam.dir.x >= 0) - (game->cam.dir.x < 0);
	step->y = (game->cam.dir.y >= 0) - (game->cam.dir.y < 0);
	dist[0].x = (map->x + 1.0 - game->cam.pos.x) * dist[1].x;
	dist[0].y = (map->y + 1.0 - game->cam.pos.y) * dist[1].y;
	if (game->cam.dir.x < 0)
		dist[0].x = (game->cam.pos.x - map->x) * dist[1].x;
	if (game->cam.dir.y < 0)
		dist[0].y = (game->cam.pos.y - map->y) * dist[1].y;
}

static void	check_portal(t_app *app, t_game *game)
{
	t_ixy	map;
	t_dxy	ray[2];
	t_ixy	step;
	double	dist;
	t_idx	i;

	set_portal_ray(game, &map, ray, &step);
	i = -1;
	while (++i < 2)
	{
		if (ray[0].x < ray[0].y)
		{
			dist = ray[0].x;
			ray[0].x += ray[1].x;
			map.x += step.x;
		}
		else
		{
			dist = ray[0].y;
			ray[0].y += ray[1].y;
			map.y += step.y;
		}
		if (dist > 1.5 || check_portal_tile(app, game, map))
			return ;
	}
}

int	key_press(int keycode, t_app *app)
{
	t_game	*game;
	t_idx	i;

	if (keycode == XKEY_ESC)
		close_app(app);
	game = &app->core.games[app->core.curr_game];
	if (game->state.hero_hp <= 0
		|| app->screen.dissolve.mode != GAME)
		return (0);
	if (keycode == XKEY_SPACE)
		return (check_portal(app, game), 0);
	if (keycode == XKEY_Z || keycode == XKEY_X || keycode == XKEY_C)
	{
		if (!game->hud.hand.is_shot)
			switch_hand(game, keycode);
		else if (game->hud.hand.queue_tail
			- game->hud.hand.queue_head < 32)
			game->hud.hand.queue
			[game->hud.hand.queue_tail++ % 32] = keycode;
		return (0);
	}
	i = get_key_idx(keycode);
	if (i >= 0)
		app->input.keys[i] = TRUE;
	return (0);
}

#endif
