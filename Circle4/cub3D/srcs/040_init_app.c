/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   019_init_app.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ucho <ucho@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/09 04:48:46 by ucho              #+#    #+#             */
/*   Updated: 2026/07/09 04:48:46 by ucho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

int	init_mlx(t_core *core)
{
	core->mlx = mlx_init();
	if (!core->mlx)
		return (put_err("MLX", "mlx_init failed"));
	core->win = mlx_new_window(core->mlx, WIN_W, WIN_H, "cub3D");
	if (!core->win)
		return (destroy_mlx(core), put_err("MLX", "mlx_new_window failed"));
	core->screen.img = mlx_new_image(core->mlx, REND_W, REND_H);
	if (!core->screen.img)
		return (destroy_mlx(core), put_err("MLX", "mlx_new_image failed"));
	core->screen.addr = mlx_get_data_addr(core->screen.img,
			&core->screen.bpp, &core->screen.line_len, &core->screen.endian);
	core->screen.size.w = REND_W;
	core->screen.size.h = REND_H;
	core->display.img = mlx_new_image(core->mlx, WIN_W, WIN_H);
	if (!core->display.img)
		return (destroy_mlx(core), put_err("MLX", "mlx_new_image failed"));
	core->display.addr = mlx_get_data_addr(core->display.img,
			&core->display.bpp, &core->display.line_len,
			&core->display.endian);
	core->display.size.w = WIN_W;
	core->display.size.h = WIN_H;
	return (SUCCESS);
}

#ifndef BONUS

static void	init_camera(t_game *game)
{
	game->cam.v_fov = 1.5;
	game->cam.pos.x = game->scene.pos.x + 0.5;
	game->cam.pos.y = game->scene.pos.y + 0.5;
	game->cam.dir.x = game->scene.dir.x;
	game->cam.dir.y = game->scene.dir.y;
	game->cam.plane.x = game->scene.plane.x;
	game->cam.plane.y = game->scene.plane.y;
}

void	init_app(t_app *app, t_game *game)
{
	if (init_mlx(&app->core))
	{
		destroy_app(app);
		exit(FAILURE);
	}
	init_camera(game);
	if (load_wall(app, game))
	{
		destroy_app(app);
		exit(FAILURE);
	}
}

#endif
