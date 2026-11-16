/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ucho <ucho@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 11:31:24 by ucho              #+#    #+#             */
/*   Updated: 2024/10/16 16:43:10 by ucho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*result;
	int		i;
	size_t	len;

	if (!s || !f)
		return (NULL);
	i = 0;
	len = ft_strlen((char *)s);
	result = (char *)malloc(len + 1);
	if (!result)
		return (NULL);
	while (len)
	{
		result[i] = f(i, s[i]);
		len--;
		i++;
	}
	result[i] = '\0';
	return (result);
}
