/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   007_is_valid.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ucho <ucho@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/09 04:48:04 by ucho              #+#    #+#             */
/*   Updated: 2026/07/09 04:48:05 by ucho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

int	is_valid_id(char *line, const char *id)
{
	t_idx	i;

	line = ft_strskip(line, ft_isspace, FALSE);
	i = 0;
	while (id[i])
	{
		if (id[i] == 'a')
		{
			if (line[i] < 'a' || line[i] > 'z')
				return (FALSE);
		}
		else if (line[i] != id[i])
			return (FALSE);
		i++;
	}
	return (line[i] == '\0' || ft_isspace(line[i]));
}

#ifndef BONUS

int	is_valid_premap(t_game *game)
{
	if (!game->asset.wall_base[WALL_NORTH].path
		|| !game->asset.wall_base[WALL_SOUTH].path
		|| !game->asset.wall_base[WALL_WEST].path
		|| !game->asset.wall_base[WALL_EAST].path)
		return (put_err("PARSE", "NO/SO/WE/EA are unvalid"), FALSE);
	if (game->asset.rgb[FLOOR] == -1
		|| game->asset.rgb[CEIL] == -1)
		return (put_err("PARSE", "F/C are unvalid"), FALSE);
	return (TRUE);
}

#endif
