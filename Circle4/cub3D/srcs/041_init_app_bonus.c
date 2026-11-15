/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   049_init_app_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ucho <ucho@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/09 04:50:08 by ucho              #+#    #+#             */
/*   Updated: 2026/07/09 04:50:09 by ucho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D_bonus.h>

#ifdef BONUS

static int	init_screen(t_app *app)
{
	app->rend.depth = (double *)ft_xmalloc(sizeof(double)
			* REND_W * REND_H);
	if (load_font(app))
		return (FAILURE);
	if (load_intro(app) || load_outro(app))
		return (FAILURE);
	if (load_minimap(app))
		return (FAILURE);
	return (SUCCESS);
}

static int	load_hud(t_app *app, t_game *game)
{
	t_tex	*tex;
	t_idx	i;

	i = -1;
	while (++i < game->asset.hud.vec.len)
	{
		tex = (t_tex *)vec_at(&game->asset.hud.vec, i);
		if (load_xpm_image(app, tex->path, &tex->img))
			return (put_load_err("H", tex->path));
	}
	return (SUCCESS);
}

static int	init_texture(t_app *app)
{
	t_idx	i;

	i = -1;
	while (++i < app->core.game_count)
	{
		if (load_wall(app, &app->core.games[i]))
			return (FAILURE);
		load_background(app, &app->core.games[i]);
		if (load_hand(app, &app->core.games[i]))
			return (FAILURE);
		if (load_hud(app, &app->core.games[i]))
			return (FAILURE);
		if (load_prop(app, &app->core.games[i]))
			return (FAILURE);
		if (load_item(app, &app->core.games[i]))
			return (FAILURE);
		if (load_door(app, &app->core.games[i]))
			return (FAILURE);
		if (load_mob(app, &app->core.games[i]))
			return (FAILURE);
	}
	return (SUCCESS);
}

static void	init_gear_charge(t_game *game)
{
	int		charge;
	t_idx	i;

	i = -1;
	charge = 0;
	while (++i < SLOT_COUNT)
	{
		game->state.gear_charge[i] = -1;
		if (game->asset.hand_shot[i].vec.len)
		{
			game->state.gear_charge[i] = 0;
			if (charge < HERO_GEAR && ++game->state.gear_charge[i])
				charge++;
		}
	}
	i = 0;
	while (charge < HERO_GEAR)
	{
		if (game->asset.hand_shot[i].vec.len
			&& ++game->state.gear_charge[i])
			charge++;
		if (++i >= SLOT_COUNT)
			i = 0;
	}
}

void	init_app(t_app *app, t_game *game)
{
	if (init_mlx(&app->core))
	{
		destroy_app(app);
		exit(FAILURE);
	}
	if (init_screen(app))
	{
		destroy_app(app);
		exit(FAILURE);
	}
	if (init_texture(app))
	{
		destroy_app(app);
		exit(FAILURE);
	}
	init_gear_charge(game);
	init_runtime(app, game);
	app->screen.dissolve.mode = INTRO_TITLE;
	save_snapshot(game);
}

#endif
