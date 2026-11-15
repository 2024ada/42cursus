/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   012_load_xpm.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ucho <ucho@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/09 04:48:20 by ucho              #+#    #+#             */
/*   Updated: 2026/07/09 04:48:20 by ucho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

int	load_xpm_image(t_app *app, char *path, t_img *tex)
{
	if (tex->img)
		mlx_destroy_image(app->core.mlx, tex->img);
	ft_bzero(tex, sizeof(t_img));
	tex->img = mlx_xpm_file_to_image(app->core.mlx, path,
			&tex->size.w, &tex->size.h);
	if (!tex->img)
		return (FAILURE);
	tex->addr = mlx_get_data_addr(tex->img,
			&tex->bpp, &tex->line_len, &tex->endian);
	return (SUCCESS);
}
