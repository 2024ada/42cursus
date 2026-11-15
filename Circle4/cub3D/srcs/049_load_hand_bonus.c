/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   054_load_hand_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ucho <ucho@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/09 04:50:22 by ucho              #+#    #+#             */
/*   Updated: 2026/07/09 04:50:23 by ucho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D_bonus.h>

#ifdef BONUS

static int	load_hand_shot(t_app *app, t_game *game)
{
	t_tex	*tex;
	t_idx	i;
	t_idx	j;

	i = -1;
	while (++i < SLOT_COUNT)
	{
		j = -1;
		while (++j < game->asset.hand_shot[i].vec.len)
		{
			tex = (t_tex *)vec_at(&game->asset.hand_shot[i].vec, j);
			if (load_xpm_image(app, tex->path, &tex->img))
				return (put_load_err("P_A", tex->path));
		}
	}
	return (SUCCESS);
}

int	load_hand(t_app *app, t_game *game)
{
	t_tex	*tex;
	t_idx	i;

	i = -1;
	while (++i < game->asset.hand_idle.vec.len)
	{
		tex = (t_tex *)vec_at(&game->asset.hand_idle.vec, i);
		if (load_xpm_image(app, tex->path, &tex->img))
			return (put_load_err("P", tex->path));
	}
	i = -1;
	while (++i < game->asset.overlay_damage.vec.len)
	{
		tex = (t_tex *)vec_at(&game->asset.overlay_damage.vec, i);
		if (load_xpm_image(app, tex->path, &tex->img))
			return (put_load_err("P_D", tex->path));
	}
	if (load_hand_shot(app, game))
		return (FAILURE);
	return (SUCCESS);
}

#endif
