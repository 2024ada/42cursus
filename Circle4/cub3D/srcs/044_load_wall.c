/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   020_load_wall.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ucho <ucho@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/09 04:48:49 by ucho              #+#    #+#             */
/*   Updated: 2026/07/09 04:48:50 by ucho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

#ifndef BONUS

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
	return (SUCCESS);
}

#endif
