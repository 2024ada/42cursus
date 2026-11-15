/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   101_destroy_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ucho <ucho@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/09 04:52:23 by ucho              #+#    #+#             */
/*   Updated: 2026/07/09 05:05:29 by ucho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D_bonus.h>

#ifdef BONUS

void	free_tex(void *elem)
{
	t_tex	*tex;

	tex = (t_tex *)elem;
	free(tex->path);
	tex->path = NULL;
}

void	destroy_texture_vec(t_app *app, t_vec *texs)
{
	t_tex	*tex;
	t_idx	i;

	i = -1;
	while (++i < texs->len)
	{
		tex = (t_tex *)vec_at(texs, i);
		destroy_image(app->core.mlx, &tex->img);
	}
	vec_free(texs);
}

void	remove_tex(t_app *app, t_vec *texs, t_idx i)
{
	t_tex	*tex;
	t_tex	*next;

	tex = (t_tex *)vec_at(texs, i);
	if (tex)
	{
		destroy_image(app->core.mlx, &tex->img);
		free(tex->path);
	}
	while (i + 1 < texs->len)
	{
		tex = (t_tex *)vec_at(texs, i);
		next = (t_tex *)vec_at(texs, i + 1);
		*tex = *next;
		i++;
	}
	texs->len--;
}

void	init_cub(t_game *game)
{
	t_idx	i;
	t_idx	j;

	vec_init(&game->asset.background[0].vec, sizeof(t_tex), 4, free_tex);
	vec_init(&game->asset.background[1].vec, sizeof(t_tex), 4, free_tex);
	vec_init(&game->asset.wall_deco.vec, sizeof(t_tex), 8, free_tex);
	vec_init(&game->asset.hand_idle.vec, sizeof(t_tex), 8, free_tex);
	vec_init(&game->asset.hud.vec, sizeof(t_tex), 12, free_tex);
	vec_init(&game->asset.overlay_damage.vec, sizeof(t_tex), 4, free_tex);
	vec_init(&game->entity.props, sizeof(t_prop), 8, NULL);
	vec_init(&game->entity.items, sizeof(t_item), 16, NULL);
	vec_init(&game->entity.mobs, sizeof(t_mob), 16, NULL);
	vec_init(&game->snapshot.entity.props, sizeof(t_prop), 8, NULL);
	vec_init(&game->snapshot.entity.items, sizeof(t_item), 16, NULL);
	vec_init(&game->snapshot.entity.mobs, sizeof(t_mob), 16, NULL);
	i = -1;
	while (++i < 26)
	{
		vec_init(&game->asset.hand_shot[i].vec, sizeof(t_tex), 0, free_tex);
		vec_init(&game->asset.item_heal[i].vec, sizeof(t_tex), 0, free_tex);
		vec_init(&game->asset.item_gear[i].vec, sizeof(t_tex), 0, free_tex);
		j = -1;
		while (++j < MOB_COUNT)
			vec_init(&game->asset.mobs[j][i].vec, sizeof(t_tex), 0, free_tex);
	}
}

t_img	*get_vec_img(t_vec *vec, t_idx i)
{
	t_tex	*tex;

	if (!vec || i < 0 || i >= vec->len)
		return (NULL);
	tex = (t_tex *)vec_at(vec, i);
	if (!tex || !tex->img.img)
		return (NULL);
	return (&tex->img);
}

#endif
