/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   073_draw_doorfaces_bonus.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ucho <ucho@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/09 04:51:09 by ucho              #+#    #+#             */
/*   Updated: 2026/07/09 04:51:09 by ucho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D_bonus.h>

#ifdef BONUS

void	draw_doorhead(t_app *app, t_game *game, t_pos x)
{
	t_sample	span[2];
	double		step;
	t_idx		i;

	if (!app->rend.hit.face)
		return ;
	step = (app->rend.hit.span[1] - app->rend.hit.span[0]) / 160.0;
	if (step <= 0.0)
		return ;
	span[0].dist = -1.0;
	i = -1;
	while (++i <= 160)
	{
		if (set_doorhead_sample(game, app->rend.hit,
				app->rend.hit.span[0] + step * (double)i, &span[1]))
		{
			if (span[0].dist > 0.0)
				draw_doorhead_span(app, game, x, span);
			span[0] = span[1];
		}
		else
			span[0].dist = -1.0;
	}
}

static void	draw_left_span(t_app *app, t_game *game,
	t_pos x, t_sample span[2])
{
	t_pos		y[2];
	double		ratio;
	t_sample	pt;

	if ((int)span[0].screen_y == (int)span[1].screen_y)
		return ;
	y[0] = (int)fmin(span[0].screen_y, span[1].screen_y);
	y[1] = (int)fmax(span[0].screen_y, span[1].screen_y);
	(void)(TRUE && (y[0] = max(y[0], 0) - 1, y[1] = min(y[1], REND_H - 1)));
	while (++y[0] <= y[1])
	{
		ratio = ((double)y[0] - span[0].screen_y)
			/ (span[1].screen_y - span[0].screen_y);
		if (ratio >= 0.0 && ratio <= 1.0)
		{
			pt.dist = span[0].dist + (span[1].dist - span[0].dist) * ratio;
			pt.local.x = span[0].local.x
				+ (span[1].local.x - span[0].local.x) * ratio;
			pt.local.y = span[0].local.y
				+ (span[1].local.y - span[0].local.y) * ratio;
			pt.z = span[0].z + (span[1].z - span[0].z) * ratio;
			pt.screen_y = (double)y[0];
			draw_left_pixel(app, game, (t_ixy){x, y[0]}, pt);
		}
	}
}

void	draw_doorleft(t_app *app, t_game *game, t_pos x)
{
	t_sample	span[2];
	int			count;
	int			frame_y;
	t_img		*frame;
	t_idx		i;

	frame = &game->asset.door[DOOR_FRAME][get_tile(game,
			app->rend.hit.face->map.x, app->rend.hit.face->map.y) - 'a'].img;
	if (frame->size.h <= 1)
		return ;
	count = min(frame->size.h, 220);
	span[0].dist = -1.0;
	i = -1;
	while (++i < count)
	{
		frame_y = (int)((double)(frame->size.h - 1)
				* (double)i / (double)(count - 1));
		if (set_left_sample(game, app->rend.hit, frame_y, &span[1]))
		{
			(span[0].dist > 0.0) && (draw_left_span(app, game, x, span), TRUE);
			span[0] = span[1];
		}
		else
			span[0].dist = -1.0;
	}
}

static void	draw_right_span(t_app *app, t_game *game, t_pos x,
	t_sample span[2])
{
	t_pos		y[2];
	double		ratio;
	t_sample	pt;

	if ((int)span[0].screen_y == (int)span[1].screen_y)
		return ;
	y[0] = (int)fmin(span[0].screen_y, span[1].screen_y);
	y[1] = (int)fmax(span[0].screen_y, span[1].screen_y);
	(void)(TRUE && (y[0] = max(y[0], 0) - 1, y[1] = min(y[1], REND_H - 1)));
	while (++y[0] <= y[1])
	{
		ratio = ((double)y[0] - span[0].screen_y)
			/ (span[1].screen_y - span[0].screen_y);
		if (ratio >= 0.0 && ratio <= 1.0)
		{
			pt.dist = span[0].dist + (span[1].dist - span[0].dist) * ratio;
			pt.local.x = span[0].local.x
				+ (span[1].local.x - span[0].local.x) * ratio;
			pt.local.y = span[0].local.y
				+ (span[1].local.y - span[0].local.y) * ratio;
			pt.z = span[0].z + (span[1].z - span[0].z) * ratio;
			pt.screen_y = (double)y[0];
			draw_right_pixel(app, game, (t_ixy){x, y[0]}, pt);
		}
	}
}

void	draw_doorright(t_app *app, t_game *game, t_pos x)
{
	t_sample	span[2];
	int			count;
	int			frame_y;
	t_img		*frame;
	t_idx		i;

	frame = &game->asset.door[DOOR_FRAME][get_tile(game,
			app->rend.hit.face->map.x, app->rend.hit.face->map.y) - 'a'].img;
	if (frame->size.h <= 1)
		return ;
	count = min(frame->size.h, 220);
	span[0].dist = -1.0;
	i = -1;
	while (++i < count)
	{
		frame_y = (int)((double)(frame->size.h - 1)
				* (double)i / (double)(count - 1));
		if (set_right_sample(game, app->rend.hit, frame_y, &span[1]))
		{
			(span[0].dist > 0.0) && (draw_right_span(app, game, x, span), TRUE);
			span[0] = span[1];
		}
		else
			span[0].dist = -1.0;
	}
}

#endif
