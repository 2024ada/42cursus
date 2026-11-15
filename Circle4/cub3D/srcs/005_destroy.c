/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   004_destroy.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ucho <ucho@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/09 04:47:56 by ucho              #+#    #+#             */
/*   Updated: 2026/07/09 04:47:57 by ucho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

void	free_split(char **arr)
{
	t_idx	i;

	i = 0;
	if (!arr)
		return ;
	while (arr[i])
		free(arr[i++]);
	free(arr);
}

void	free_str(void *elem)
{
	char	**str_ptr;

	str_ptr = (char **)elem;
	if (str_ptr && *str_ptr)
		free(*str_ptr);
}

void	destroy_img(void *mlx, t_img *img)
{
	if (img->img)
	{
		mlx_destroy_image(mlx, img->img);
		img->img = NULL;
	}
}

void	destroy_image(void *mlx, t_img *img)
{
	if (img->img)
	{
		mlx_destroy_image(mlx, img->img);
		img->img = NULL;
	}
}

void	destroy_mlx(t_core *core)
{
	if (!core || !core->mlx)
		return ;
	destroy_image(core->mlx, &core->screen);
	destroy_image(core->mlx, &core->display);
	if (core->win)
		mlx_destroy_window(core->mlx, core->win);
	mlx_destroy_display(core->mlx);
	free(core->mlx);
	ft_bzero(core, sizeof(*core));
}
