/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   013_parse_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ucho <ucho@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/09 04:48:22 by ucho              #+#    #+#             */
/*   Updated: 2026/07/09 04:48:23 by ucho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

t_idx	get_id_idx(const char **array, const char *target)
{
	t_idx	i;

	if (!array || !target)
		return (-1);
	i = 0;
	while (array[i])
	{
		if (!ft_strncmp(target, array[i], ft_strlen(array[i])))
			return (i);
		i++;
	}
	return (-1);
}
