/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   063_init_item_gear_bonus.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ucho <ucho@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/09 04:50:46 by ucho              #+#    #+#             */
/*   Updated: 2026/07/09 04:50:47 by ucho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D_bonus.h>

#ifdef BONUS

static void	fill_gear_tile(t_game *game, t_ixy *cand, int *count)
{
	t_pos	x;
	t_pos	y;

	*count = 0;
	y = -1;
	while (++y < game->scene.map.size.h)
	{
		x = -1;
		while (++x < game->scene.map.size.w)
		{
			if (is_empty_tile(game, (t_ixy){x, y}))
			{
				cand[*count] = (t_ixy){x, y};
				(*count)++;
			}
		}
	}
}

void	init_item_gear(t_game *game)
{
	t_ixy	*cand;
	t_idx	types[SLOT_COUNT];
	t_num	count;

	cand = ft_xmalloc(sizeof(t_ixy) * game->scene.map.size.w
			* game->scene.map.size.h);
	fill_gear_tile(game, cand, &count);
	set_item_gear(game, cand, count, types);
	free(cand);
}

#endif
