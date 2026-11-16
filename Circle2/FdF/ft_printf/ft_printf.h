/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ucho <ucho@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 03:12:43 by ucho              #+#    #+#             */
/*   Updated: 2025/08/07 01:59:41 by ucho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "libft/libft.h"
# include <stdlib.h>
# include <unistd.h>
# include <stdarg.h>
# define INDICATOR '%'
# define TRUE 1
# define FALSE 0
# define STDOUT_FILENO 1
# define INT_MAX 2147483647

typedef struct s_flag
{
	int			minus;
	int			plus;
	int			zero;
	long long	width;
	int			point;
	long long	precision;
	int			sharp;
	int			space;
	int			is_uppercase;
}	t_flag;

int			ft_printf(const char *format, ...);
void		put_format(const char *format, va_list args, int *bytes);
const char	*put_args(const char *format, va_list args, int *bytes, int *err);
int			is_token(char token);
const char	*get_token(const char *text);
int			put_token(char token, va_list args, int *bytes, t_flag *flag);
void		put_space(int bytes);
char		*ft_strcpy(char *dest, const char *src);
void		put_char(va_list args, int *bytes, t_flag *flag);
void		put_string(va_list args, int *bytes, t_flag *flag);
void		put_int(va_list args, int *bytes, t_flag *flag);
int			ft_intlen(int nbr);
int			get_space(int d, int *bytes, char *s, t_flag *flag);
char		*get_int(long long n, long long size, int plus);
void		put_unsigned_int(va_list args, int *bytes, t_flag *flag);
int			ft_unsigned_intlen(unsigned int nbr);
char		*get_unsigned_int(unsigned int n, long long size);
void		put_hex(va_list args, int *bytes, t_flag *flag);
int			ft_hexlen(unsigned int nbr);
char		*get_hex(unsigned int n, long long size,
				int sharp, int is_uppercase);
void		put_pointer(va_list args, int *len, t_flag *flag);
int			ft_addrlen(unsigned long long p, int *prefix, t_flag *flag);
char		*get_nil(void);
char		*get_addr(unsigned long long addr, t_flag *flag);
t_flag		*set_flag(void);
t_flag		*get_flag(const char *format);
void		parse_flag(t_flag *flag, const char **format);
int			parse_width(t_flag *flag, const char **format);
int			parse_precision(t_flag *flag, const char **format);
int			filter_flag(int marker, long long *size, long long n, t_flag *flag);
int			put_flag(int *bytes, t_flag *flag);
int			put_field(int num);

#endif
