/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cut_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ucho <ucho@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 02:29:52 by ada               #+#    #+#             */
/*   Updated: 2025/07/31 11:38:18 by ucho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	get_tockenlen(const char *s, int *i, char delim)
{
	char	quote;
	int		start;

	while (s[*i] && s[*i] == delim)
		(*i)++;
	if (!s[*i])
		return (0);
	start = *i;
	if (s[*i] == '\'' || s[*i] == '\"')
	{
		quote = s[*i];
		(*i)++;
		while (s[*i] && s[*i] != quote)
			(*i)++;
		if (s[*i] == quote)
			(*i)++;
	}
	else
	{
		while (s[*i] && s[*i] != delim && s[*i] != '\'' && s[*i] != '\"')
			(*i)++;
	}
	return (*i - start);
}

char	*get_str(char *str, int start, int len)
{
	char	*word;
	int		i;

	if (len >= 2 && str[start] == '\'' && str[start + len - 1] == '\'')
	{
		len -= 2;
		start += 1;
	}
	word = (char *)malloc(sizeof(char) * (len + 1));
	if (!word)
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

char	**get_strs(char **strs, char *str, char charset, int count)
{
	int		len;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (i < count)
	{
		while (str[j] && str[j] == charset)
			j++;
		len = get_tockenlen(str, &j, charset);
		strs[i] = get_str(str, j - len, len);
		if (!strs[i])
			return (let_strs(strs), NULL);
		i++;
	}
	strs[i] = NULL;
	return (strs);
}

char	**set_strs(char *str, char charset, int count)
{
	char	**strs;

	strs = (char **)malloc(sizeof(char *) * (count + 1));
	if (!strs)
		return (NULL);
	strs[count] = NULL;
	return (get_strs(strs, str, charset, count));
}

char	**cut_cmd(const char *s, char c)
{
	int		count;
	int		i;
	int		len;

	if (!s)
		return (NULL);
	count = 0;
	i = 0;
	while (s[i])
	{
		len = get_tockenlen(s, &i, c);
		if (len > 0)
			count++;
	}
	return (set_strs((char *)s, c, count));
}
