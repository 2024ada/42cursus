/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   002_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ucho <ucho@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/09 04:47:51 by ucho              #+#    #+#             */
/*   Updated: 2026/07/09 04:47:52 by ucho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

char	*ft_strpbrk(const char *str, const char *accept)
{
	while (*str)
	{
		if (ft_strchr(accept, *str))
			return ((char *)str);
		str++;
	}
	return (NULL);
}

char	*ft_strskip(char *str, int (*ft)(char), int invert)
{
	if (!str || !ft)
		return (str);
	if (invert)
		while (*str && !ft((unsigned char)*str))
			str++;
	else
		while (*str && ft((unsigned char)*str))
			str++;
	return (str);
}

int	ft_isspace(char c)
{
	return (c == ' ' || c == '\t' || c == '\n');
}

int	min(int a, int b)
{
	if (a < b)
		return (a);
	return (b);
}

int	max(int a, int b)
{
	if (a > b)
		return (a);
	return (b);
}
