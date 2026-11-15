/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   027_player_rotate.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ucho <ucho@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/09 04:49:06 by ucho              #+#    #+#             */
/*   Updated: 2026/07/09 04:49:06 by ucho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

void	rotate_left(t_game *game, double rot)
{
	double	dir;
	double	plane;

	dir = game->cam.dir.x;
	game->cam.dir.x = game->cam.dir.x * cos(-rot) - game->cam.dir.y * sin(-rot);
	game->cam.dir.y = dir * sin(-rot) + game->cam.dir.y * cos(-rot);
	plane = game->cam.plane.x;
	game->cam.plane.x
		= game->cam.plane.x * cos(-rot) - game->cam.plane.y * sin(-rot);
	game->cam.plane.y = plane * sin(-rot) + game->cam.plane.y * cos(-rot);
}

void	rotate_right(t_game *game, double rot)
{
	double	dir;
	double	plane;

	dir = game->cam.dir.x;
	game->cam.dir.x = game->cam.dir.x * cos(rot) - game->cam.dir.y * sin(rot);
	game->cam.dir.y = dir * sin(rot) + game->cam.dir.y * cos(rot);
	plane = game->cam.plane.x;
	game->cam.plane.x
		= game->cam.plane.x * cos(rot) - game->cam.plane.y * sin(rot);
	game->cam.plane.y = plane * sin(rot) + game->cam.plane.y * cos(rot);
}
