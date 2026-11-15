/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   017_parse_color.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ucho <ucho@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/09 04:48:41 by ucho              #+#    #+#             */
/*   Updated: 2026/07/09 04:48:41 by ucho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

#ifndef BONUS

int	parse_color(t_game *game, char *line, t_idx type)
{
	(void)game;
	(void)type;
	line = ft_strskip(line, ft_isspace, FALSE);
	if (*line)
		return (put_err("PARSE", "Extra token after RGB color"));
	return (SUCCESS);
}

#endif
