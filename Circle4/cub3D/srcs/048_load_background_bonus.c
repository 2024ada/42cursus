/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   053_load_background_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ucho <ucho@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/09 04:50:18 by ucho              #+#    #+#             */
/*   Updated: 2026/07/09 04:50:18 by ucho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D_bonus.h>

#ifdef BONUS

static void	load_floor(t_app *app, t_game *game, char *path)
{
	t_vec	*vec;
	t_tex	*tex;
	t_bool	fallback;
	t_idx	i;

	vec = &game->asset.background[FLOOR].vec;
	fallback = FALSE;
	i = 0;
	while (i < vec->len)
	{
		tex = (t_tex *)vec_at(vec, i);
		if (!load_xpm_image(app, tex->path, &tex->img))
			fallback |= (i++ == 0);
		else if (i == 0)
			(put_load_err("F", tex->path),
				vec_free(vec), vec_init(vec, sizeof(t_tex), 4, free_tex));
		else
		{
			put_load_err("F", tex->path);
			if (fallback && path && !load_xpm_image(app, path, &tex->img))
				i++;
			else
				remove_tex(app, vec, i);
		}
	}
}

void	load_background(t_app *app, t_game *game)
{
	t_tex	*tex;
	char	*path;
	t_idx	i;

	path = NULL;
	tex = (t_tex *)vec_at(&game->asset.background[FLOOR].vec, 0);
	if (tex)
		path = tex->path;
	load_floor(app, game, path);
	i = 0;
	while (i < game->asset.background[CEIL].vec.len)
	{
		tex = (t_tex *)vec_at(&game->asset.background[CEIL].vec, i);
		if (load_xpm_image(app, tex->path, &tex->img))
		{
			put_load_err("C", tex->path);
			remove_tex(app, &game->asset.background[CEIL].vec, i);
		}
		else
			i++;
	}
}

#endif
