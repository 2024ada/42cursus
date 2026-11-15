/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   067_draw_ceil_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ucho <ucho@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/09 04:50:55 by ucho              #+#    #+#             */
/*   Updated: 2026/07/09 04:50:55 by ucho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D_bonus.h>

#ifdef BONUS

static void	set_ceil_frame(t_game *game, t_ceil_anim *ceil)
{
	double	elapsed;
	double	step;
	t_idx	frame;

	elapsed = game->state.now - game->state.ceil_started_at;
	elapsed = fmax(elapsed, 0.0);
	step = elapsed / CEIL_DISSOLVE_TIME;
	frame = (int)step;
	if (frame >= game->asset.background[1].vec.len - 1)
	{
		game->state.ceil_done = TRUE;
		ceil->curr = get_vec_img(&game->asset.background[1].vec,
				game->asset.background[1].vec.len - 1);
		return ;
	}
	ceil->curr = get_vec_img(&game->asset.background[1].vec, frame);
	ceil->next = get_vec_img(&game->asset.background[1].vec, frame + 1);
	ceil->alpha = step - (double)frame;
	ceil->alpha = fmin(fmax(ceil->alpha, 0.0), 1.0);
	if (!ceil->next)
		ceil->alpha = 0.0;
}

static void	set_ceil(t_game *game, t_ceil_anim *ceil)
{
	ft_bzero(ceil, sizeof(*ceil));
	if (game->asset.background[1].vec.len <= 0)
		return ;
	if (game->asset.background[1].vec.len == 1)
	{
		ceil->curr = get_vec_img(&game->asset.background[1].vec, 0);
		return ;
	}
	if (game->state.ceil_done == FALSE && game->state.num_goal < GAME_HALF)
	{
		ceil->curr = get_vec_img(&game->asset.background[1].vec, 0);
		return ;
	}
	if (game->state.ceil_done == TRUE)
	{
		ceil->curr = get_vec_img(&game->asset.background[1].vec,
				game->asset.background[1].vec.len - 1);
		return ;
	}
	if (game->state.ceil_started_at <= 0.0
		&& game->state.num_goal >= GAME_HALF)
		game->state.ceil_started_at = game->state.now;
	set_ceil_frame(game, ceil);
}

void	draw_ceil(t_img *screen, t_game *game)
{
	int		color;
	t_pos	x;
	t_pos	y;

	set_ceil(game, &game->runtime.ceil);
	x = -1;
	while (++x < REND_W)
	{
		y = -1;
		while (++y < REND_H / 2)
		{
			if (game->runtime.ceil.curr)
			{
				color = get_scaled_pixel(game->runtime.ceil.curr,
						(t_ixy){x, y}, REND_W, REND_H / 2);
				if (game->runtime.ceil.next && game->runtime.ceil.alpha > 0.0)
					color = blend_color(color, get_scaled_pixel
							(game->runtime.ceil.next, (t_ixy){x, y}, REND_W,
								REND_H / 2), game->runtime.ceil.alpha);
				put_pixel(screen, (t_ixy){x, y}, color);
			}
			else
				put_pixel(screen, (t_ixy){x, y}, game->asset.rgb[CEIL]);
		}
	}
}

#endif
