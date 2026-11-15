/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_art_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ucho <ucho@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 12:55:35 by ucho              #+#    #+#             */
/*   Updated: 2026/01/29 04:20:11 by ucho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

void		put_asciiart(const char **logo_map, const char **color_map);
const char	**get_logo1(void);
const char	**get_logo2(void);
const char	**get_cmap1(void);
const char	**get_cmap2(void);

void	put_intro(void)
{
	ft_putstr_fd("\033[H\033[2J", STDOUT);
	put_asciiart(get_logo1(), get_cmap1());
	put_asciiart(get_logo2(), get_cmap2());
}

void	put_asciiart(const char **logo_map, const char **color_map)
{
	const char	*ansi[] = {"\033[1;38;2;204;135;94m", "\033[1;38;2;122;59;37m",
		"\033[1;38;2;81;38;26m", "\033[1;38;2;229;229;44m", "\033[0m", NULL};
	char		*color;
	t_idx		i;
	t_idx		j;

	i = 0;
	while (logo_map[i] && color_map[i])
	{
		j = -1;
		color = NULL;
		while (++j < (long long)ft_strlen(color_map[i]))
		{
			if ((char *)ansi[color_map[i][j] - '0'] != color)
			{
				color = (char *)ansi[color_map[i][j] - '0'];
				ft_putstr_fd(color, STDOUT);
			}
			write(STDOUT, &logo_map[i][j * 3], 3);
		}
		color = (char *)ansi[4];
		ft_putstr_fd(color, STDOUT);
		ft_putendl_fd("", STDOUT);
		i++;
	}
}
