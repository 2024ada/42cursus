/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   052_load_wall_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ucho <ucho@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/09 04:50:15 by ucho              #+#    #+#             */
/*   Updated: 2026/07/09 04:50:16 by ucho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D_bonus.h>

#ifdef BONUS

static void	load_wall_deco(t_app *app, t_game *game)
{
	t_tex	*tex;
	t_idx	i;

	i = -1;
	while (++i < game->asset.wall_deco.vec.len)
	{
		tex = (t_tex *)vec_at(&game->asset.wall_deco.vec, i);
		if (load_xpm_image(app, tex->path, &tex->img))
		{
			put_load_err("T", tex->path);
			remove_tex(app, &game->asset.wall_deco.vec, i);
			continue ;
		}
	}
}

int	load_wall(t_app *app, t_game *game)
{
	const char	*names[] = {"NO", "SO", "WE", "EA", NULL};
	t_idx		i;

	i = -1;
	while (++i < WALL_DIR_COUNT)
	{
		if (game->asset.wall_base[i].path
			&& load_xpm_image(app, game->asset.wall_base[i].path,
				&game->asset.wall_base[i].img))
			return (put_load_err(names[i], game->asset.wall_base[i].path));
	}
	if (game->asset.wall_goal.path
		&& load_xpm_image(app, game->asset.wall_goal.path,
			&game->asset.wall_goal.img))
		return (put_load_err("G", game->asset.wall_goal.path));
	load_wall_deco(app, game);
	return (SUCCESS);
}

#endif
