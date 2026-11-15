/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   074_billboard_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ucho <ucho@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/09 04:51:21 by ucho              #+#    #+#             */
/*   Updated: 2026/07/09 05:32:48 by ucho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D_bonus.h>

#ifdef BONUS

static int	set_billboard(t_cam	*cam, t_tex *tex,
	double bill[3], t_billboard *board)
{
	double	inv;
	double	plane;
	double	ratio;
	double	width;
	double	stretch;

	inv = 1.0 / (cam->plane.x * cam->dir.y - cam->dir.x * cam->plane.y);
	board->trans.x = inv * (cam->dir.y * bill[0] - cam->dir.x * bill[1]);
	board->trans.y = inv * (-cam->plane.y * bill[0] + cam->plane.x * bill[1]);
	if (board->trans.y <= 0)
		return (0);
	board->wall.w = (int)fabs(REND_H / board->trans.y);
	board->wall.h = (int)fabs((REND_H / board->trans.y) * cam->v_fov);
	ratio = (double)tex->img.size.w / (double)tex->img.size.h;
	plane = sqrt(cam->plane.x * cam->plane.x
			+ cam->plane.y * cam->plane.y);
	(plane < 0.0001) && (plane = 1.0, TRUE);
	board->screen.x = (int)((REND_W / 2)
			* (1 + board->trans.x / board->trans.y));
	board->size.h = (int)(board->wall.h * bill[2]);
	board->pitch = (cam->eye_level + 100.0) / board->trans.y;
	width = board->wall.w * cam->default_v_fov * bill[2] * ratio;
	stretch = ((double)REND_W / 1920.0) / ((double)REND_H / 1080.0);
	board->size.w = (int)(width * (cam->default_plane_len / plane) * stretch);
	return (board->size.w > 0 && board->size.h > 0);
}

static void	draw_billboard_pixel(t_app *app, t_tex *tex, t_billboard *board)
{
	t_ixy			pos;
	t_ixy			img;
	int				ofs;

	pos.x = board->start.x - 1;
	while (++pos.x < board->end.x)
	{
		if (pos.x > 0 && pos.x < REND_W)
		{
			img.x = (pos.x - board->real.x) * tex->img.size.w / board->size.w;
			pos.y = board->start.y - 1;
			while (++pos.y < board->end.y)
			{
				if (board->trans.y < app->rend.depth[pos.y * REND_W + pos.x])
				{
					ofs = pos.y - board->real.y;
					img.y = ofs * tex->img.size.h / board->size.h;
					img.y = min(max(img.y, 0), tex->img.size.h - 1);
					if (!is_transparent_color(get_pixel(&tex->img, img)))
						put_pixel(&app->core.screen, pos,
							get_pixel(&tex->img, img));
				}
			}
		}
	}
}

void	draw_billboard(t_app *app, t_game *game,
	t_tex *tex, double bill[3])
{
	t_billboard	board;

	if (!set_billboard(&game->cam, tex, bill, &board))
		return ;
	board.real.y = REND_H / 2 + board.wall.h / 2
		- board.size.h + board.pitch;
	board.start.y = max(board.real.y, 0);
	board.end.y = min(REND_H / 2 + board.wall.h / 2
			+ board.pitch, REND_H - 1);
	board.real.x = -board.size.w / 2 + board.screen.x;
	board.start.x = max(board.real.x, 0);
	board.end.x = min(board.size.w / 2 + board.screen.x, REND_W - 1);
	draw_billboard_pixel(app, tex, &board);
}

#endif
