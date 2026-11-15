/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   006_ids.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ucho <ucho@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/09 04:48:02 by ucho              #+#    #+#             */
/*   Updated: 2026/07/09 04:48:02 by ucho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

#ifndef BONUS

const char	**required_ids(void)
{
	static const char	*ids[] = {
		"NO",
		"SO",
		"WE",
		"EA",
		"F",
		"C",
		NULL
	};

	return (ids);
}

int	is_valid_sign(char c)
{
	const char	symbols[] = " 01NSEW";

	return (ft_strchr(symbols, c) != NULL);
}

int	is_walkable_sign(char c)
{
	const char	symbols[] = "0NSEW";

	return (ft_strchr(symbols, c) != NULL);
}

int	is_zone_sign(char c)
{
	const char	symbols[] = "0NSEW";

	return (ft_strchr(symbols, c) != NULL);
}

#endif
