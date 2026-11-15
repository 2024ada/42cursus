/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   086_fov_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ucho <ucho@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/09 04:51:47 by ucho              #+#    #+#             */
/*   Updated: 2026/07/09 04:51:47 by ucho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D_bonus.h>

#ifdef BONUS

void	increase_hfov(t_game *game)
{
	double	len;
	double	ratio;

	len = sqrt(game->cam.plane.x * game->cam.plane.x
			+ game->cam.plane.y * game->cam.plane.y);
	if (len >= H_FOV_MAX)
		return ;
	game->cam.plane.x *= 1.03;
	game->cam.plane.y *= 1.03;
	len = sqrt(game->cam.plane.x * game->cam.plane.x
			+ game->cam.plane.y * game->cam.plane.y);
	if (len <= 0.0001)
		return ;
	ratio = fmin(len, H_FOV_MAX) / len;
	game->cam.plane.x *= ratio;
	game->cam.plane.y *= ratio;
}

void	decrease_hfov(t_game *game)
{
	double	len;
	double	ratio;

	len = sqrt(game->cam.plane.x * game->cam.plane.x
			+ game->cam.plane.y * game->cam.plane.y);
	if (len <= H_FOV_MIN)
		return ;
	game->cam.plane.x *= 0.97;
	game->cam.plane.y *= 0.97;
	len = sqrt(game->cam.plane.x * game->cam.plane.x
			+ game->cam.plane.y * game->cam.plane.y);
	if (len <= 0.0001)
		return ;
	ratio = fmax(len, H_FOV_MIN) / len;
	game->cam.plane.x *= ratio;
	game->cam.plane.y *= ratio;
}

void	increase_vfov(t_game *game)
{
	if (game->cam.v_fov >= V_FOV_MAX)
		return ;
	game->cam.v_fov *= 1.03;
	game->cam.v_fov = fmin(game->cam.v_fov, V_FOV_MAX);
}

void	decrease_vfov(t_game *game)
{
	if (game->cam.v_fov <= V_FOV_MIN)
		return ;
	game->cam.v_fov *= 0.97;
	game->cam.v_fov = fmax(game->cam.v_fov, V_FOV_MIN);
}

#endif
