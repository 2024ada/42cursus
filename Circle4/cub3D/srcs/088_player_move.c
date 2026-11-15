/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   026_player_move.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ucho <ucho@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/09 04:49:04 by ucho              #+#    #+#             */
/*   Updated: 2026/07/09 04:49:04 by ucho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

void	move_forward(t_game *game, double speed)
{
	double	new_x;
	double	new_y;

	new_x = game->cam.pos.x + game->cam.dir.x * speed;
	new_y = game->cam.pos.y + game->cam.dir.y * speed;
	if (!is_hero_blocked(game, new_x, game->cam.pos.y))
		game->cam.pos.x = new_x;
	if (!is_hero_blocked(game, game->cam.pos.x, new_y))
		game->cam.pos.y = new_y;
}

void	move_backward(t_game *game, double speed)
{
	double	new_x;
	double	new_y;

	new_x = game->cam.pos.x - game->cam.dir.x * speed;
	new_y = game->cam.pos.y - game->cam.dir.y * speed;
	if (!is_hero_blocked(game, new_x, game->cam.pos.y))
		game->cam.pos.x = new_x;
	if (!is_hero_blocked(game, game->cam.pos.x, new_y))
		game->cam.pos.y = new_y;
}

void	strafe_left(t_game *game, double speed)
{
	t_dxy	strafe;
	t_dxy	next;

	strafe.x = game->cam.dir.y;
	strafe.y = -game->cam.dir.x;
	next.x = game->cam.pos.x + strafe.x * speed;
	next.y = game->cam.pos.y + strafe.y * speed;
	if (!is_hero_blocked(game, next.x, game->cam.pos.y))
		game->cam.pos.x = next.x;
	if (!is_hero_blocked(game, game->cam.pos.x, next.y))
		game->cam.pos.y = next.y;
}

void	strafe_right(t_game *game, double speed)
{
	t_dxy	strafe;
	t_dxy	next;

	strafe.x = -game->cam.dir.y;
	strafe.y = game->cam.dir.x;
	next.x = game->cam.pos.x + strafe.x * speed;
	next.y = game->cam.pos.y + strafe.y * speed;
	if (!is_hero_blocked(game, next.x, game->cam.pos.y))
		game->cam.pos.x = next.x;
	if (!is_hero_blocked(game, game->cam.pos.x, next.y))
		game->cam.pos.y = next.y;
}
