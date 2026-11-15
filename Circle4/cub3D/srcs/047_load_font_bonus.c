/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   051_load_font_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ucho <ucho@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/09 04:50:13 by ucho              #+#    #+#             */
/*   Updated: 2026/07/09 04:50:13 by ucho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D_bonus.h>

#ifdef BONUS

static char	*set_font_path(int index)
{
	char	*num;
	char	*path;
	size_t	len;

	num = ft_itoa(index);
	len = ft_strlen(FONT) + ft_strlen(num) + ft_strlen(".xpm") + 1;
	if (len > INT_MAX)
		return (free(num), NULL);
	path = (char *)ft_xmalloc(len);
	ft_strlcpy(path, FONT, len);
	ft_strlcat(path, num, len);
	ft_strlcat(path, ".xpm", len);
	return (free(num), path);
}

int	load_font(t_app *app)
{
	char	*path;
	t_idx	i;

	i = -1;
	while (++i < FONT_COUNT)
	{
		path = set_font_path(i);
		if (!path)
			return (put_err("Font", "font path is too long"));
		if (load_xpm_image(app, path, &app->assets.font[i]))
			return (free(path), 1);
		free(path);
	}
	return (0);
}

#endif
