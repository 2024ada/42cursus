/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   059_set_wall_deco_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ucho <ucho@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/09 04:50:37 by ucho              #+#    #+#             */
/*   Updated: 2026/07/09 04:50:38 by ucho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D_bonus.h>

#ifdef BONUS

double	get_prop_half(t_img *img)
{
	t_ixy	range;
	t_ixy	pixel;

	if (!img || !img->img || img->size.w <= 0 || img->size.h <= 0)
		return (0.0);
	range.x = img->size.w;
	range.y = -1;
	pixel.y = -1;
	while (++pixel.y < img->size.h)
	{
		pixel.x = -1;
		while (++pixel.x < img->size.w)
		{
			if (!is_transparent_color(get_pixel(img, pixel)))
			{
				range.x = min(range.x, pixel.x);
				range.y = max(range.y, pixel.x);
			}
		}
	}
	if (range.x > range.y)
		return (0.0);
	return ((PROP_SCALE * (double)(range.y - range.x + 1)
		/ (double)img->size.h) / 2.0);
}

static void	mix_wall_deco(t_ixy *cand, t_num count)
{
	t_ixy	temp;
	t_idx	pick;
	t_idx	i;

	i = count - 1;
	while (i > 0)
	{
		pick = ft_rand() % (i + 1);
		temp = cand[i];
		cand[i] = cand[pick];
		cand[pick] = temp;
		i--;
	}
}

static void	fill_wall_deco(t_game *game, t_ixy *cand, t_num count)
{
	t_pos	x;
	t_pos	y;
	t_idx	i;

	i = 0;
	y = -1;
	while (++y < game->scene.map.size.h)
	{
		x = -1;
		while (++x < game->scene.map.size.w)
		{
			if (game->scene.map.grid[y][x] == '1')
			{
				cand[i] = (t_ixy){x, y};
				i++;
			}
		}
	}
	mix_wall_deco(cand, count);
}

static int	pick_wall_deco(t_game *game, t_num	*quotas)
{
	t_num	count;
	t_idx	pick;
	t_idx	i;

	count = 0;
	i = -1;
	while (++i < game->asset.wall_deco.vec.len)
		if (quotas[i] > 0)
			count += quotas[i];
	if (count == 0)
		return (-1);
	pick = ft_rand() % count;
	i = -1;
	while (++i < game->asset.wall_deco.vec.len)
	{
		if (quotas[i])
		{
			if (pick < quotas[i])
				return (i);
			pick -= quotas[i];
		}
	}
	return (-1);
}

void	set_wall_deco(t_game *game, t_num num_wall, t_num num_deco)
{
	t_ixy	*cand;
	t_num	*quotas;
	t_idx	deco;
	t_idx	i;

	cand = ft_xmalloc(sizeof(t_ixy) * num_wall);
	quotas = ft_xmalloc(sizeof(int) * game->asset.wall_deco.vec.len);
	fill_wall_deco(game, cand, num_wall);
	i = -1;
	while (++i < game->asset.wall_deco.vec.len)
		quotas[i] = num_deco / game->asset.wall_deco.vec.len;
	i = -1;
	while (++i < num_deco % game->asset.wall_deco.vec.len)
		quotas[i]++;
	i = -1;
	while (++i < num_wall)
	{
		deco = pick_wall_deco(game, quotas);
		if (deco < 0)
			break ;
		game->scene.map.deco[cand[i].y][cand[i].x] = deco;
		quotas[deco]--;
	}
	free(cand);
	free(quotas);
}

#endif
