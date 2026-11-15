/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   066_rend_app_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ucho <ucho@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/09 04:50:53 by ucho              #+#    #+#             */
/*   Updated: 2026/07/09 04:50:53 by ucho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D_bonus.h>

#ifdef BONUS

static void	draw_background(t_app *app, t_game *game)
{
	draw_ceil(&app->core.screen, game);
	draw_floor(&app->core.screen, game);
}

static void	draw_walls(t_app *app, t_game *game)
{
	int		max;
	t_pos	x;

	max = game->scene.map.size.w + game->scene.map.size.h + 1;
	app->rend.hit.walls = ft_xmalloc(sizeof(t_face) * max);
	app->rend.hit.doors = ft_xmalloc(sizeof(t_face) * max);
	app->rend.hit.face = NULL;
	x = -1;
	while (++x < REND_W)
		draw_wall(app, game, x);
	free(app->rend.hit.walls);
	free(app->rend.hit.doors);
	app->rend.hit.walls = NULL;
	app->rend.hit.doors = NULL;
}

static void	draw_hand(t_app *app, t_game *game)
{
	t_vec	*hand;
	t_tex	*tex;

	hand = &game->asset.hand_shot[game->hud.hand.base_gear].vec;
	if (game->hud.hand.mode == HAND_IDLE)
		hand = &game->asset.hand_idle.vec;
	set_hand(game, hand);
	hand = &game->asset.hand_shot[game->hud.hand.base_gear].vec;
	if (game->hud.hand.mode == HAND_IDLE)
		hand = &game->asset.hand_idle.vec;
	tex = (t_tex *)vec_at(hand, game->hud.hand.frame);
	draw_overlay(app, &tex->img);
}

static void	draw_effect(t_app *app, t_game *game)
{
	t_vec	*effect;
	t_tex	*tex;

	effect = &game->asset.overlay_damage.vec;
	set_effect(app, game, effect);
	if (game->hud.effect.mode == NONE)
		return ;
	tex = (t_tex *)vec_at(effect, game->hud.effect.frame);
	draw_overlay(app, &tex->img);
}

void	rend_app(t_app *app, t_game *game)
{
	t_idx	i;

	i = 0;
	while (i < REND_W * REND_H)
		app->rend.depth[i++] = 1e30;
	draw_background(app, game);
	draw_walls(app, game);
	draw_sprites(app, game);
	draw_hand(app, game);
	draw_effect(app, game);
	draw_hud(app, game);
	draw_minimap(app, game);
	draw_outro(app, game);
	draw_intro(app, game);
	draw_screen(app);
	draw_window(app);
}

#endif
