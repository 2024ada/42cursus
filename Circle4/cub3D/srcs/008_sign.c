/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   005_sign.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ucho <ucho@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/09 04:48:00 by ucho              #+#    #+#             */
/*   Updated: 2026/07/09 04:48:00 by ucho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

int	is_door_sign(char tile)
{
	return ('a' <= tile && tile <= 'z');
}

int	is_wall_sign(char tile)
{
	const char	symbols[] = "1G";

	return (ft_strchr(symbols, tile) || is_door_sign(tile));
}
