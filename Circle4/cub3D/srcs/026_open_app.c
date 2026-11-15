/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   026_open_app.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ucho <ucho@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/09 04:48:36 by ucho              #+#    #+#             */
/*   Updated: 2026/07/09 08:03:15 by ucho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

static int	read_cub(t_game *game, int fd, t_vec *lines)
{
	char	*line;
	char	*newl;
	t_idx	i;

	line = get_nextline(fd);
	while (line != NULL)
	{
		newl = ft_strchr(line, '\n');
		if (newl)
			*newl = '\0';
		i = ft_strskip(line, ft_isspace, FALSE) - line;
		if (!line[i] && lines->len)
			return (free(line), put_err("MAP", "Empty line in map"));
		else if (line[i] && lines->len)
		{
			if (parse_map(game, line, lines))
				return (free(line), FAILURE);
		}
		else if (line[i] && parse_premap(game, line, lines))
			return (free(line), FAILURE);
		free(line);
		line = get_nextline(fd);
	}
	return (SUCCESS);
}

int	load_cub(t_game *game, int fd)
{
	t_vec	map;
	char	*line;
	size_t	len;
	t_idx	i;

	vec_init(&map, sizeof(char *), 16, free_str);
	if (read_cub(game, fd, &map))
		return (get_nextline(-42), vec_free(&map), FAILURE);
	if (game->scene.count != 1)
		return (vec_free(&map), put_err("MAP", "No player in map"));
	game->scene.map.grid = ft_xmalloc(sizeof(char *)
			* (game->scene.map.size.h + 1));
	i = -1;
	while (++i < game->scene.map.size.h)
	{
		line = *(char **)vec_at(&map, i);
		len = ft_strlen(line);
		game->scene.map.grid[i] = ft_xmalloc(game->scene.map.size.w + 1);
		ft_memmove(game->scene.map.grid[i], line, len);
		ft_memset(game->scene.map.grid[i] + len,
			' ', game->scene.map.size.w - len);
		game->scene.map.grid[i][game->scene.map.size.w] = '\0';
	}
	game->scene.map.grid[i] = NULL;
	return (vec_free(&map), SUCCESS);
}

#ifndef BONUS

static int	check_cub(t_game *game)
{
	if (is_closed_map(game))
		return (put_err("MAP", "Map is not closed by walls"));
	return (SUCCESS);
}

int	open_cub(char *path, t_game *game)
{
	char	*file;
	int		fd;
	size_t	len;

	game->asset.rgb[0] = -1;
	game->asset.rgb[1] = -1;
	file = ft_strrchr(path, '/');
	if (file)
		file++;
	else
		file = path;
	len = ft_strlen(file);
	if (len < 4 || ft_strcmp(file + len - 4, ".cub"))
		return (put_err("INPUT", "The map extension must be '.cub'"));
	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (put_err("INPUT", "Cannot open map(.cub) file"));
	if (load_cub(game, fd) || check_cub(game))
		return (close(fd), FAILURE);
	return (close(fd), SUCCESS);
}

#endif

void	open_app(int argc, char **argv, t_app *app)
{
	t_idx	i;
	t_idx	j;

	if (argc < 2 || argc > GAME_MAX + 1)
		exit(put_err("INPUT", "USAGE : ./cub3d [Map file]"));
	ft_bzero(app, sizeof(t_app));
	app->core.game_count = argc - 1;
	app->core.curr_game = 0;
	i = 0;
	while (++i < argc)
	{
		if (open_cub(argv[i], &app->core.games[i - 1]))
		{
			j = -1;
			while (++j < i)
				free_cub(app, &app->core.games[j]);
			exit(FAILURE);
		}
	}
}
