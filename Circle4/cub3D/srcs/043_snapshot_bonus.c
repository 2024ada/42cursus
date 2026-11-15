/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   058_snapshot_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ucho <ucho@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/09 04:50:35 by ucho              #+#    #+#             */
/*   Updated: 2026/07/09 04:50:36 by ucho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D_bonus.h>

#ifdef BONUS

static int	get_default_gear(t_game *game)
{
	t_idx	i;

	i = 0;
	while (i < SLOT_COUNT)
	{
		if (game->asset.hand_shot[i].vec.len)
			return (i);
		i++;
	}
	return (0);
}

void	reset_runtime(t_app *app, t_game *game)
{
	ft_bzero(&app->input, sizeof(app->input));
	ft_bzero(&app->screen, sizeof(app->screen));
	ft_bzero(&game->hud, sizeof(game->hud));
	game->hud.hand.base_gear = get_default_gear(game);
	game->state.now = get_now();
}

static void	reset_door_anim(t_game *game)
{
	t_pos	y;

	if (!game->scene.map.door)
		return ;
	y = -1;
	while (++y < game->scene.map.size.h)
	{
		ft_bzero(game->scene.map.door[y],
			sizeof(t_dmap) * game->scene.map.size.w);
	}
}

void	save_snapshot(t_game *game)
{
	game->snapshot.state = game->state;
	game->snapshot.cam = game->cam;
	vec_copy(&game->snapshot.entity.props, &game->entity.props);
	vec_copy(&game->snapshot.entity.items, &game->entity.items);
	vec_copy(&game->snapshot.entity.mobs, &game->entity.mobs);
}

void	load_snapshot(t_app *app, t_game *game)
{
	game->state = game->snapshot.state;
	game->cam = game->snapshot.cam;
	vec_copy(&game->entity.props, &game->snapshot.entity.props);
	vec_copy(&game->entity.items, &game->snapshot.entity.items);
	vec_copy(&game->entity.mobs, &game->snapshot.entity.mobs);
	reset_door_anim(game);
	reset_runtime(app, game);
}

#endif
