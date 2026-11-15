/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ucho <ucho@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 11:30:51 by ucho              #+#    #+#             */
/*   Updated: 2024/10/16 17:33:52 by ucho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static void	free_strs(char **strs, int i)
{
	while (i >= 0)
	{
		free(strs[i]);
		i--;
	}
	free(strs);
}

static char	*fill_str(char *str, int start, int len)
{
	char	*word;
	int		i;

	word = (char *)malloc(sizeof(char) * (len + 1));
	if (word == NULL)
		return (NULL);
	i = 0;
	while (i < len)
	{
		word[i] = str[start + i];
		i++;
	}
	word[len] = '\0';
	return (word);
}

static char	**fill_strs(char **strs, char *str, char charset, int count)
{
	int	i;
	int	j;
	int	len;

	i = 0;
	j = 0;
	while (i < count)
	{
		while (str[j] && str[j] == charset)
			j++;
		len = j;
		while (str[j] && str[j] != charset)
			j++;
		strs[i] = fill_str(str, len, j - len);
		if (strs[i] == NULL)
		{
			free_strs(strs, i - 1);
			return (NULL);
		}
		i++;
	}
	return (strs);
}

static char	**allocate_strs(char *str, char charset, int count)
{
	char	**strs;

	strs = (char **)malloc(sizeof(char *) * (count + 1));
	if (strs == NULL)
		return (NULL);
	strs[count] = NULL;
	return (fill_strs(strs, str, charset, count));
}

char	**ft_split(char const *s, char c)
{
	int	count;
	int	is_str;
	int	i;

	if (!s)
		return (NULL);
	i = 0;
	count = 0;
	is_str = 0;
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		is_str = i;
		while (s[i] && s[i] != c)
			i++;
		if (is_str < i)
			count++;
	}
	return (allocate_strs((char *)s, c, count));
}
