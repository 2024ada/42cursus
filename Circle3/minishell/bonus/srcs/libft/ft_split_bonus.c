/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ucho <ucho@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 11:30:51 by ucho              #+#    #+#             */
/*   Updated: 2026/01/29 04:21:58 by ucho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_libft_bonus.h"

static char	*fill_str(char *str, int start, int len)
{
	char	*word;
	int		i;

	word = (char *)ft_xmalloc(sizeof(char) * (len + 1));
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
		i++;
	}
	return (strs);
}

static char	**allocate_strs(char *str, char charset, int count)
{
	char	**strs;

	strs = (char **)ft_xmalloc(sizeof(char *) * (count + 1));
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
