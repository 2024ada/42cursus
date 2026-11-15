/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   003_put_err.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ucho <ucho@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/09 04:47:54 by ucho              #+#    #+#             */
/*   Updated: 2026/07/09 04:47:54 by ucho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

int	put_err(char *type, char *message)
{
	ft_putendl_fd("Error", STDERR);
	if (type)
	{
		ft_putstr_fd("[", STDERR);
		ft_putstr_fd(type, STDERR);
		ft_putstr_fd("] ", STDERR);
	}
	ft_putendl_fd(message, STDERR);
	return (FAILURE);
}

int	put_load_err(const char *kind, char *path)
{
	put_err("TEXTURE", "Failed to load ");
	ft_putstr_fd((char *)kind, STDERR);
	ft_putstr_fd(": ", STDERR);
	ft_putendl_fd(path, STDERR);
	return (FAILURE);
}
