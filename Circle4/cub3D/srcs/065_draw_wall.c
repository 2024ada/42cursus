/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   022_draw_wall.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ucho <ucho@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/09 04:48:54 by ucho              #+#    #+#             */
/*   Updated: 2026/07/09 04:48:55 by ucho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

void	init_ray(t_ray *ray, t_game *game, t_pos x)
{
	ray->camera_x = 2.0 * x / (double)REND_W - 1.0;
	ray->dir.x = game->cam.dir.x + game->cam.plane.x * ray->camera_x;
	ray->dir.y = game->cam.dir.y + game->cam.plane.y * ray->camera_x;
	ray->map.x = (int)game->cam.pos.x;
	ray->map.y = (int)game->cam.pos.y;
	ray->delta_dist.x = 1e30;
	ray->delta_dist.y = 1e30;
	if (ray->dir.x)
		ray->delta_dist.x = fabs(1.0 / ray->dir.x);
	if (ray->dir.y)
		ray->delta_dist.y = fabs(1.0 / ray->dir.y);
	ray->step.x = 2 * (ray->dir.x >= 0) - 1;
	ray->side_dist.x = (game->cam.pos.x - ray->map.x) * ray->delta_dist.x;
	if (ray->dir.x >= 0)
		ray->side_dist.x = ray->delta_dist.x - ray->side_dist.x;
	ray->step.y = 2 * (ray->dir.y >= 0) - 1;
	ray->side_dist.y = (game->cam.pos.y - ray->map.y) * ray->delta_dist.y;
	if (ray->dir.y >= 0)
		ray->side_dist.y = ray->delta_dist.y - ray->side_dist.y;
}

static int	set_wallface(t_game *game, t_ray_hit hit, t_ixy map)
{
	double	dist;

	if (hit.ray.side == 0)
	{
		if (hit.ray.dir.x == 0.0)
			return (0);
		dist = (hit.ray.map.x - game->cam.pos.x
				+ (1 - hit.ray.step.x) / 2.0) / hit.ray.dir.x;
	}
	else
	{
		if (hit.ray.dir.y == 0.0)
			return (0);
		dist = (hit.ray.map.y - game->cam.pos.y
				+ (1 - hit.ray.step.y) / 2.0) / hit.ray.dir.y;
	}
	if (dist <= 0.0)
		return (0);
	hit.face->map.x = map.x;
	hit.face->map.y = map.y;
	hit.face->side = hit.ray.side;
	hit.face->dist = dist;
	return (1);
}

static int	add_wallface(t_game *game, t_ray_hit hit, t_ixy prev)
{
	if (is_wall_sign(get_tile(game, hit.ray.map.x, hit.ray.map.y))
		&& !is_wall_sign(get_tile(game, prev.x, prev.y)))
		return (set_wallface(game, hit, hit.ray.map));
	if (!is_wall_sign(get_tile(game, hit.ray.map.x, hit.ray.map.y))
		&& is_wall_sign(get_tile(game, prev.x, prev.y)))
		return (set_wallface(game, hit, prev));
	return (0);
}

int	collect_wallfaces(t_game *game, t_ray_hit hit)
{
	t_ixy	prev;
	t_num	count;

	count = 0;
	while (count < game->scene.map.size.w + game->scene.map.size.h + 1)
	{
		prev = hit.ray.map;
		if (hit.ray.side_dist.x < hit.ray.side_dist.y)
		{
			hit.ray.side_dist.x += hit.ray.delta_dist.x;
			hit.ray.map.x += hit.ray.step.x;
			hit.ray.side = 0;
		}
		else
		{
			hit.ray.side_dist.y += hit.ray.delta_dist.y;
			hit.ray.map.y += hit.ray.step.y;
			hit.ray.side = 1;
		}
		if (!is_in_map(game, hit.ray.map.x, hit.ray.map.y))
			break ;
		hit.face = &hit.walls[count];
		count += add_wallface(game, hit, prev);
	}
	return (count);
}

#ifndef BONUS

void	draw_wall(t_app *app, t_game *game, t_pos x)
{
	t_num	wallfaces;

	app->rend.hit.face = NULL;
	init_ray(&app->rend.hit.ray, game, x);
	wallfaces = collect_wallfaces(game, app->rend.hit);
	draw_wallfaces(app, game, wallfaces, x);
}

#endif
