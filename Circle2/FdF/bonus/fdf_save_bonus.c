/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_save_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ucho <ucho@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 15:11:17 by ucho              #+#    #+#             */
/*   Updated: 2025/08/19 14:14:19 by ucho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

static int	write_ppm_header(int fd)
{
	char	*width;
	char	*height;

	width = ft_itoa(MAP_W);
	if (!width)
		return (-1);
	height = ft_itoa(MAP_H);
	if (!height)
	{
		free(width);
		return (-1);
	}
	ft_putstr_fd("P6\n", fd);
	ft_putstr_fd(width, fd);
	ft_putstr_fd(" ", fd);
	ft_putstr_fd(height, fd);
	ft_putstr_fd("\n255\n", fd);
	free(width);
	free(height);
	return (0);
}

static void	write_ppm_body(int fd, t_img img)
{
	unsigned char	*buf;
	unsigned char	*p;
	unsigned int	color;
	int				x;
	int				y;

	buf = malloc(MAP_W * 3);
	if (!buf)
		return ;
	y = MAP_Y - 1;
	while (++y < WIN_H)
	{
		p = buf;
		x = MAP_X - 1;
		while (++x < WIN_W)
		{
			color = *(unsigned int *)(img.addr
					+ y * img.line_len + x * (img.bpp / 8));
			*p++ = (color >> 16) & 0xFF;
			*p++ = (color >> 8) & 0xFF;
			*p++ = color & 0xFF;
		}
		write(fd, buf, MAP_W * 3);
	}
	free(buf);
}

void	save_ppm(t_file file, t_img img)
{
	int		output;
	char	*name;

	name = get_ppm_name(file);
	if (!name)
		return ;
	output = open(name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (output < 0)
	{
		put_error("Error: Failed to save file\n");
		free(name);
		return ;
	}
	if (write_ppm_header(output) < 0)
	{
		close(output);
		free(name);
		return ;
	}
	write_ppm_body(output, img);
	close(output);
	ft_printf("%s saved\n", name);
	free(name);
}
