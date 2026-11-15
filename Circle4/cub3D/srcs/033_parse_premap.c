/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   016_parse_premap.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ucho <ucho@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/09 04:48:38 by ucho              #+#    #+#             */
/*   Updated: 2026/07/09 04:48:39 by ucho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

int	parse_wall(t_game *game, char *line, const char **wall)
{
	char	*path;
	size_t	len;
	t_idx	i;

	i = get_id_idx(wall, line);
	if (game->asset.wall_base[i].path)
		return (put_err("PARSE", "Duplicate path found"));
	line += ft_strlen(wall[i]);
	line = ft_strskip(line, ft_isspace, FALSE);
	if (!*line)
		return (put_err("PARSE", "Empty texture path"));
	path = line;
	len = ft_strskip(line, ft_isspace, TRUE) - line;
	if (len < 4 || ft_strncmp(path + len - 4, ".xpm", 4))
		return (put_err("PARSE", "Texture path must end with '.xpm'"));
	line = ft_strskip(path + len, ft_isspace, FALSE);
	if (*line)
		return (put_err("PARSE", "Extra token after texture path"));
	game->asset.wall_base[i].path = ft_substr(path, 0, len);
	return (SUCCESS);
}

static char	*parse_rgb(char *line, int *color)
{
	long long	value;
	t_num		count;

	count = 0;
	*color = 0;
	while (count < 3)
	{
		line = ft_strskip(line, ft_isspace, FALSE);
		if (!ft_isdigit(*line))
			return (NULL);
		value = 0;
		while (ft_isdigit(*line))
			value = value * 10 + (*line++ - '0');
		if (value > 255)
			return (NULL);
		*color = (*color << 8) | (int)value;
		line = ft_strskip(line, ft_isspace, FALSE);
		if (++count < 3)
		{
			if (*line != ',')
				return (NULL);
			line++;
		}
	}
	return (line);
}

int	parse_background(t_game *game, char *line, const char **surface)
{
	int		color;
	t_idx	i;

	i = get_id_idx(surface, line);
	if (game->asset.rgb[i] != -1)
		return (put_err("PARSE", "Duplicate path found"));
	line += ft_strlen(surface[i]);
	line = parse_rgb(line, &color);
	if (!line)
		return (put_err("PARSE", "RGB format must be R,G,B"));
	game->asset.rgb[i] = color;
	return (parse_color(game, line, i));
}

#ifndef BONUS

static int	parse_header(t_game *game, char *line)
{
	const char	*wall[] = {"NO", "SO", "WE", "EA", NULL};
	const char	*surface[] = {"F", "C", NULL};
	t_idx		i;

	line = ft_strskip(line, ft_isspace, FALSE);
	i = 0;
	while (wall[i])
	{
		if (is_valid_id(line, wall[i]))
			return (parse_wall(game, line, wall));
		i++;
	}
	i = 0;
	while (surface[i])
	{
		if (is_valid_id(line, surface[i]))
			return (parse_background(game, line, surface));
		i++;
	}
	return (put_err("PARSE", "Invalid texture identifier"));
}

int	parse_premap(t_game *game, char *line, t_vec *lines)
{
	const char	**req_ids = required_ids();
	t_idx		i;

	i = 0;
	while (req_ids[i])
	{
		if (is_valid_id(line, req_ids[i]))
			return (parse_header(game, line));
		i++;
	}
	if (!is_valid_premap(game))
		return (FAILURE);
	return (parse_map(game, line, lines));
}

#endif
