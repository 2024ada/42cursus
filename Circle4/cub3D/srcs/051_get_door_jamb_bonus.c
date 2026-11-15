/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   056_get_door_jamb_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ucho <ucho@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/09 04:50:31 by ucho              #+#    #+#             */
/*   Updated: 2026/07/09 04:50:31 by ucho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D_bonus.h>

#ifdef BONUS

static void	get_door_head(t_img *tex, t_door_shape *door, unsigned char *mask)
{
	t_pos	x;
	t_pos	y;

	door->jamb_head = (double *)ft_xmalloc(sizeof(double) * tex->size.w);
	x = -1;
	while (++x < tex->size.w)
	{
		door->jamb_head[x] = -1.0;
		y = -1;
		while (++y < tex->size.h)
		{
			if (mask[y * tex->size.w + x])
			{
				door->jamb_head[x] = 1.0
					- ((double)y / (double)tex->size.h);
				break ;
			}
		}
	}
}

static void	flood_fill_mask(t_img *tex, unsigned char *mask,
	t_idx *queue, t_idx tail)
{
	t_idx	head;
	t_idx	i;
	t_pos	x;

	head = 0;
	while (head < tail)
	{
		i = queue[head++];
		x = i % tex->size.w;
		if (x > 0 && is_transparent_pixel(tex, mask, i - 1))
			(void)(TRUE && (mask[i - 1] = 1, queue[tail++] = i - 1));
		if (x + 1 < tex->size.w && is_transparent_pixel(tex, mask, i + 1))
			(void)(TRUE && (mask[i + 1] = 1, queue[tail++] = i + 1));
		if (i >= tex->size.w
			&& is_transparent_pixel(tex, mask, i - tex->size.w))
			(void)(TRUE && (mask[i - tex->size.w] = 1,
					queue[tail++] = i - tex->size.w));
		if (i + tex->size.w < tex->size.w * tex->size.h
			&& is_transparent_pixel(tex, mask, i + tex->size.w))
			(void)(TRUE && (mask[i + tex->size.w] = 1,
				queue[tail++] = i + tex->size.w));
	}
}

static unsigned char	*make_door_mask(t_img *tex, t_door_shape *door)
{
	unsigned char	*mask;
	t_idx			*queue;
	t_idx			tail;
	t_idx			i;
	t_pos			x;

	mask = (unsigned char *)ft_calloc(tex->size.w * tex->size.h,
			sizeof(unsigned char));
	queue = (int *)ft_xmalloc(sizeof(int) * tex->size.w * tex->size.h);
	tail = 0;
	x = tex->size.w / 4;
	while (x < tex->size.w - (tex->size.w / 4))
	{
		i = (tex->size.h - 1) * tex->size.w + x;
		if (is_transparent_pixel(tex, mask, i))
		{
			mask[i] = 1;
			queue[tail++] = i;
		}
		x++;
	}
	flood_fill_mask(tex, mask, queue, tail);
	free(queue);
	get_door_head(tex, door, mask);
	return (mask);
}

static int	has_door_portal(t_img *tex, t_door_shape *door)
{
	t_pos	left;
	t_pos	right;
	t_pos	y;

	door->jamb_left = (int *)ft_xmalloc(sizeof(int) * tex->size.h);
	door->jamb_right = (int *)ft_xmalloc(sizeof(int) * tex->size.h);
	y = -1;
	while (++y < tex->size.h)
	{
		door->jamb_left[y] = tex->size.w;
		door->jamb_right[y] = -1;
	}
	left = 0;
	while (left < tex->size.w && !has_transparent_pixel(tex, left))
		left++;
	right = tex->size.w - 1;
	while (right > left && !has_transparent_pixel(tex, right))
		right--;
	return (left < right);
}

void	get_door_jamb(t_img *tex, t_door_shape *door)
{
	unsigned char	*mask;
	t_pos			y;

	if (!tex || !tex->img || tex->size.w <= 1)
		return ;
	if (!has_door_portal(tex, door))
		return ;
	mask = make_door_mask(tex, door);
	y = -1;
	while (++y < tex->size.h)
	{
		door->jamb_left[y] = -1;
		while (++door->jamb_left[y] < tex->size.w)
			if (mask[y * tex->size.w + door->jamb_left[y]])
				break ;
		door->jamb_right[y] = tex->size.w;
		while (--door->jamb_right[y] >= 0)
			if (mask[y * tex->size.w + door->jamb_right[y]])
				break ;
	}
	free(mask);
}

#endif
