/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   048_parse_color_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ucho <ucho@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/09 04:50:05 by ucho              #+#    #+#             */
/*   Updated: 2026/07/09 04:50:06 by ucho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D_bonus.h>

#ifdef BONUS

int	parse_color(t_game *game, char *line, t_idx type)
{
	t_tex	tex;
	char	*path;
	size_t	len;

	line = ft_strskip(line, ft_isspace, FALSE);
	while (*line)
	{
		path = line;
		len = ft_strskip(line, ft_isspace, TRUE) - line;
		if (len < 4 || ft_strncmp(path + len - 4, ".xpm", 4))
			return (put_err("PARSE", "Texture path must end with '.xpm'"));
		ft_bzero(&tex, sizeof(t_tex));
		tex.path = ft_substr(path, 0, len);
		vec_push(&game->asset.background[type].vec, &tex);
		line = ft_strskip(path + len, ft_isspace, FALSE);
	}
	return (SUCCESS);
}

#endif
