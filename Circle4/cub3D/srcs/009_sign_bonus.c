/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   031_sign_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ucho <ucho@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/09 04:49:15 by ucho              #+#    #+#             */
/*   Updated: 2026/07/09 04:49:16 by ucho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D_bonus.h>

#ifdef BONUS

int	is_walkable_sign(char tile)
{
	const char	symbols[] = "0NSEWM";

	return (ft_strchr(symbols, tile) || ft_strchr(optional_ids(), tile)
		|| is_door_sign(tile));
}

int	is_zone_sign(char tile)
{
	const char	symbols[] = "0NSEWM";

	return (ft_strchr(symbols, tile) || ft_strchr(optional_ids(), tile));
}

#endif
