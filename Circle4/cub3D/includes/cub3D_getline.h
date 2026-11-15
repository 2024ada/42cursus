/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D_getline.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ucho <ucho@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/09 05:15:28 by ucho              #+#    #+#             */
/*   Updated: 2026/07/09 05:15:35 by ucho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_GETLINE_H
# define CUB3D_GETLINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1000
# endif

typedef struct s_buf
{
	int				fd;
	char			*buf;
	struct s_buf	*next;
}	t_buf;

char	*get_nextline(int fd);

#endif
