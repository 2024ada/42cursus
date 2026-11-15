/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   047_parse_texture_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ucho <ucho@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/09 04:50:01 by ucho              #+#    #+#             */
/*   Updated: 2026/07/09 04:50:02 by ucho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D_bonus.h>

#ifdef BONUS

static int	parse_item_vec(t_tex_seq *seq, char *line, char *id)
{
	t_tex	tex;
	char	*path;
	size_t	len;

	if (seq->vec.len)
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
		return (put_err("PARSE", "Requires exactly one .xpm path"));
	ft_bzero(&tex, sizeof(t_tex));
	tex.path = ft_substr(path, 0, len);
	vec_push(&seq->vec, &tex);
	return (SUCCESS);
}

int	parse_door(t_game *game, char *line)
{
	char	*path;
	size_t	len;
	t_idx	type;
	t_idx	i;

	type = line[1] - 'a';
	if (game->asset.door[DOOR_FRAME][type].path)
		return (put_err("PARSE", "Duplicate path found"));
	line = ft_strskip(line + 2, ft_isspace, FALSE);
	if (!*line)
		return (put_err("PARSE", "Requires at least one .xpm path"));
	i = -1;
	while (*line && ++i < DOOR_COUNT)
	{
		path = line;
		len = ft_strskip(line, ft_isspace, TRUE) - line;
		if (len < 4 || ft_strncmp(path + len - 4, ".xpm", 4))
			return (free_texs(game->asset.door, type, i),
				put_err("PARSE", "Texture path must end with '.xpm'"));
		game->asset.door[i][type].path = ft_substr(path, 0, len);
		line = ft_strskip(path + len, ft_isspace, FALSE);
	}
	return (((*line || i + 1 != DOOR_COUNT)
			&& (free_texs(game->asset.door, type, i + 1), TRUE))
		&& put_err("PARSE", "Door requires 5 .xpm paths"));
}

int	parse_mob(t_game *game, char *line)
{
	t_tex_seq	*seq;
	char		id[5];

	if (line[3] == 'F')
		seq = &game->asset.mobs[MOB_FRONT][line[1] - 'a'];
	else if (line[3] == 'B')
		seq = &game->asset.mobs[MOB_BACK][line[1] - 'a'];
	else if (line[3] == 'L')
		seq = &game->asset.mobs[MOB_LEFT][line[1] - 'a'];
	else if (line[3] == 'R')
		seq = &game->asset.mobs[MOB_RIGHT][line[1] - 'a'];
	else if (line[3] == 'A')
		seq = &game->asset.mobs[MOB_ATTACK][line[1] - 'a'];
	else
		seq = &game->asset.mobs[MOB_DEATH][line[1] - 'a'];
	ft_strlcpy(id, line, sizeof(id));
	return (parse_texture_vec(seq, line, id));
}

int	parse_hand(t_game *game, char *line)
{
	if (is_valid_id(line, "P"))
		return (parse_texture_vec(&game->asset.hand_idle, line, "P"));
	if (is_valid_id(line, "P_D"))
		return (parse_texture_vec(&game->asset.overlay_damage, line, "P_D"));
	if (is_valid_id(line, "P_Aa"))
		return (parse_texture_vec(&game->asset.hand_shot[line[3] - 'a'],
				line, "P_Aa"));
	return (put_err("PARSE", "Invalid P sub-id (expected P_A[a-z] or P_D)"));
}

int	parse_item(t_game *game, char *line)
{
	if (is_valid_id(line, "I_Ha"))
		return (parse_item_vec(&game->asset.item_heal[line[3] - 'a'],
				line, "I_Ha"));
	if (is_valid_id(line, "I_Aa"))
		return (parse_item_vec(&game->asset.item_gear[line[3] - 'a'],
				line, "I_Aa"));
	if (is_valid_id(line, "I_M"))
		return (parse_texture(&game->asset.item_goal, line, "I_M"));
	return (put_err("PARSE",
			"Invalid I sub-identifier (expected I_H[a-z], I_A[a-z], or I_M)"));
}

#endif
