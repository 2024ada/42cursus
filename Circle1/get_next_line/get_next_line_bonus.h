/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ucho <ucho@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 18:05:49 by ucho              #+#    #+#             */
/*   Updated: 2025/01/24 17:06:10 by ucho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1000
# endif

typedef struct s_fd_list
{
	int					fd;
	char				*buffer;
	struct s_fd_list	*next;
}	t_fd_list;

char		*get_next_line(int fd);
t_fd_list	*add_new(t_fd_list **buffers, int fd);
char		*set_err(t_fd_list **buffers, t_fd_list *new, char **raw);
char		*set_nl(char **buffer, char **raw, int idx);
char		*set_eof(t_fd_list **buffers, t_fd_list *new, char **raw);
int			is_nl(char *buffer);
size_t		ft_strlen(const char *s);
char		*ft_strcpy(char *dest, const char *src);
char		*ft_strndup(const char *s, size_t n);
void		join_buffer(char **buffer, char *source);

#endif
