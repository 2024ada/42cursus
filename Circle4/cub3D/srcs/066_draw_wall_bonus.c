/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   071_draw_wall_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ucho <ucho@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/09 04:51:03 by ucho              #+#    #+#             */
/*   Updated: 2026/07/09 04:51:03 by ucho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D_bonus.h>

#ifdef BONUS

static int	get_doorface_span(t_game *game, t_ray_hit hit, double span[2])
{
	double	dist[2];

	if (hit.face->side == 0)
	{
		if (hit.ray.dir.x == 0.0)
			return (0);
		dist[0] = ((double)hit.face->map.x - game->cam.pos.x) / hit.ray.dir.x;
		dist[1] = ((double)hit.face->map.x + 1.0 - game->cam.pos.x)
			/ hit.ray.dir.x;
	}
	else
	{
		if (hit.ray.dir.y == 0.0)
			return (0);
		dist[0] = ((double)hit.face->map.y - game->cam.pos.y) / hit.ray.dir.y;
		dist[1] = ((double)hit.face->map.y + 1.0 - game->cam.pos.y)
			/ hit.ray.dir.y;
	}
	if (dist[0] <= 0.0 && dist[1] <= 0.0)
		return (0);
	dist[0] = fmax(dist[0], 0.0);
	dist[1] = fmax(dist[1], 0.0);
	span[0] = fmin(dist[0], dist[1]);
	span[1] = fmax(dist[0], dist[1]);
	return (span[1] > span[0]);
}

static int	add_doorface(t_game *game, t_ray_hit hit, t_num count)
{
	double	span[2];
	t_idx	i;

	i = -1;
	while (++i < count)
	{
		if (hit.doors[i].map.x == hit.ray.map.x
			&& hit.doors[i].map.y == hit.ray.map.y)
			return (0);
	}
	hit.doors[count].map.x = hit.ray.map.x;
	hit.doors[count].map.y = hit.ray.map.y;
	hit.doors[count].side = 0;
	if (is_wall_sign(get_tile(game, hit.ray.map.x - 1, hit.ray.map.y))
		&& is_wall_sign(get_tile(game, hit.ray.map.x + 1, hit.ray.map.y)))
		hit.doors[count].side = 1;
	hit.doors[count].dist = 0.0;
	hit.face = &hit.doors[count];
	if (!get_doorface_span(game, hit, span))
		return (0);
	hit.doors[count].dist = span[0];
	return (1);
}

static int	collect_doorfaces(t_game *game, t_ray_hit hit)
{
	t_num	count;

	count = 0;
	if (count < game->scene.map.size.w + game->scene.map.size.h + 1
		&& is_door_sign(get_tile(game, hit.ray.map.x, hit.ray.map.y)))
		count += add_doorface(game, hit, count);
	while (count < game->scene.map.size.w + game->scene.map.size.h + 1)
	{
		if (hit.ray.side_dist.x < hit.ray.side_dist.y)
		{
			hit.ray.side_dist.x += hit.ray.delta_dist.x;
			hit.ray.map.x += hit.ray.step.x;
		}
		else
		{
			hit.ray.side_dist.y += hit.ray.delta_dist.y;
			hit.ray.map.y += hit.ray.step.y;
		}
		if (!is_in_map(game, hit.ray.map.x, hit.ray.map.y))
			break ;
		if (is_door_sign(get_tile(game, hit.ray.map.x, hit.ray.map.y)))
			count += add_doorface(game, hit, count);
	}
	return (count);
}

static void	draw_doorfaces(t_app *app, t_game *game, t_num count, t_pos x)
{
	char	tile;
	t_idx	i;

	i = -1;
	while (++i < count)
	{
		app->rend.hit.face = &app->rend.hit.doors[i];
		tile = get_tile(game, app->rend.hit.face->map.x,
				app->rend.hit.face->map.y);
		if (tile < 'a' || tile > 'z')
			continue ;
		if (get_doorface_span(game, app->rend.hit, app->rend.hit.span))
		{
			draw_doorhead(app, game, x);
			draw_doorright(app, game, x);
			draw_doorleft(app, game, x);
		}
	}
	app->rend.hit.face = NULL;
}

void	draw_wall(t_app *app, t_game *game, t_pos x)
{
	t_num	wallfaces;
	t_num	doorfaces;

	app->rend.hit.face = NULL;
	init_ray(&app->rend.hit.ray, game, x);
	wallfaces = collect_wallfaces(game, app->rend.hit);
	doorfaces = collect_doorfaces(game, app->rend.hit);
	draw_doorfaces(app, game, doorfaces, x);
	draw_wallfaces(app, game, wallfaces, x);
}

#endif
