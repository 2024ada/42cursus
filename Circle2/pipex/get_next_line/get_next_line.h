/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ada <ada@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 18:05:56 by ucho              #+#    #+#             */
/*   Updated: 2025/05/27 06:13:20 by ada              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1000
# endif

char	*get_next_line(int fd);
int		is_nl(char *buffer);
char	*set_eof(char **buffer, char **raw);
char	*set_nl(char **buffer, char **raw, int idx);
char	*set_err(char **buffer, char **raw);
size_t	ft_strlen(const char *s);
char	*ft_strcpy(char *dest, const char *src);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strndup(const char *s, size_t n);
void	modify_buffer(char **buffer, char *source, int is_update);
char	*let_buffer(int fd, char **buffer);

#endif
