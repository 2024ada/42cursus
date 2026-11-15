/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   018_parse_map.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ucho <ucho@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/09 04:48:43 by ucho              #+#    #+#             */
/*   Updated: 2026/07/09 04:48:44 by ucho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

static int	check_map_size(t_game *game, char *line)
{
	size_t		len;
	t_dim		width;
	long long	area;
	long long	span;

	len = ft_strlen(line);
	if (len > (size_t)INT_MAX)
		return (put_err("MAP", "Map is too wide"));
	width = max(game->scene.map.size.w, (t_dim)len);
	if (game->scene.map.size.h >= INT_MAX)
		return (put_err("MAP", "Map is too tall"));
	area = (long long)width * (long long)(game->scene.map.size.h + 1);
	if (area > INT_MAX)
		return (put_err("MAP", "Map is too large"));
	span = (long long)width + (long long)(game->scene.map.size.h + 1) + 1;
	if (span > INT_MAX)
		return (put_err("MAP", "Map is too large"));
	game->scene.map.size.w = width;
	return (SUCCESS);
}

int	parse_map(t_game *game, char *row, t_vec *lines)
{
	char	*line;
	t_idx	i;

	line = ft_strdup(row);
	if (*ft_strskip(line, is_valid_sign, FALSE))
		return (free(line), put_err("MAP", "Invalid map char"));
	if (check_map_size(game, line))
		return (free(line), FAILURE);
	i = -1;
	while (line[++i])
	{
		if (ft_strchr("NSEW", line[i]))
		{
			if (game->scene.count > 0)
				return (free(line), put_err("MAP", "Only one player required"));
			game->scene.count++;
			game->scene.pos = (t_dxy){i, game->scene.map.size.h};
			game->scene.dir.x = (line[i] == 'E') - (line[i] == 'W');
			game->scene.dir.y = (line[i] == 'S') - (line[i] == 'N');
			game->scene.plane = (t_dxy){-0.6
				* game->scene.dir.y, 0.6 * game->scene.dir.x};
		}
	}
	return (game->scene.map.size.h++, vec_push(lines, &line), SUCCESS);
}
