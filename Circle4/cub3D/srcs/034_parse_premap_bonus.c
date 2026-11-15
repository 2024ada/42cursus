/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   046_parse_premap_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ucho <ucho@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/09 04:49:59 by ucho              #+#    #+#             */
/*   Updated: 2026/07/09 04:49:59 by ucho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D_bonus.h>

#ifdef BONUS

int	parse_texture_vec(t_tex_seq *seq, char *line, char *id)
{
	t_tex	tex;
	char	*path;
	size_t	len;

	if (seq->vec.len)
		return (put_err("PARSE", "Duplicate path found"));
	line += ft_strlen(id);
	line = ft_strskip(line, ft_isspace, FALSE);
	if (!*line)
		return (put_err("PARSE", "Requires at least one .xpm path"));
	while (*line)
	{
		path = line;
		len = ft_strskip(line, ft_isspace, TRUE) - line;
		if (len < 4 || ft_strncmp(path + len - 4, ".xpm", 4))
			return (put_err("PARSE", "Texture path must end with '.xpm'"));
		ft_bzero(&tex, sizeof(t_tex));
		tex.path = ft_substr(path, 0, len);
		vec_push(&seq->vec, &tex);
		line = ft_strskip(path + len, ft_isspace, FALSE);
	}
	return (SUCCESS);
}

int	parse_texture(t_tex *tex, char *line, char *id)
{
	char	*path;
	size_t	len;

	if (tex->path != NULL)
		return (put_err("PARSE", "Duplicate path found"));
	line += ft_strlen(id);
	line = ft_strskip(line, ft_isspace, FALSE);
	if (!*line)
		return (put_err("PARSE", "Empty texture path"));
	path = line;
	len = ft_strskip(line, ft_isspace, TRUE) - line;
	if (len < 4 || ft_strncmp(path + len - 4, ".xpm", 4))
		return (put_err("PARSE", "Texture path must end with '.xpm'"));
	line = ft_strskip(line + len, ft_isspace, FALSE);
	if (*line)
		return (put_err("PARSE", "requires exactly one .xpm path"));
	tex->path = ft_substr(path, 0, len);
	return (SUCCESS);
}

static int	parse_extra_header(t_game *game, char *line)
{
	if (is_valid_id(line, "T"))
		return (parse_texture_vec(&game->asset.wall_deco, line, "T"));
	if (is_valid_id(line, "G"))
		return (parse_texture(&game->asset.wall_goal, line, "G"));
	if (is_valid_id(line, "Da"))
		return (parse_door(game, line));
	if (is_valid_id(line, "H"))
		return (parse_texture_vec(&game->asset.hud, line, "H"));
	if (*line == 'M' && *(line + 1) >= 'a' && *(line + 1) <= 'z')
		return (parse_mob(game, line));
	if (*line == 'P')
		return (parse_hand(game, line));
	if (*line == 'I')
		return (parse_item(game, line));
	if (*line >= 'A' && *line <= 'Z')
		return (parse_texture(&game->asset.props[*line - 'A'],
				line, (char [2]){*line, 0}));
	return (put_err("PARSE", "Invalid texture identifier"));
}

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
	return (parse_extra_header(game, line));
}

int	parse_premap(t_game *game, char *line, t_vec *lines)
{
	const char	**req_ids = required_ids();
	const char	*opt_ids = optional_ids();
	t_idx		i;

	i = 0;
	while (req_ids[i])
	{
		if (is_valid_id(line, req_ids[i]))
			return (parse_header(game, line));
		i++;
	}
	i = 0;
	while (opt_ids[i])
	{
		if (is_valid_id(line, (char [2]){opt_ids[i], 0}))
			return (parse_header(game, line));
		i++;
	}
	if (!is_valid_premap(game))
		return (FAILURE);
	return (parse_map(game, line, lines));
}

#endif
