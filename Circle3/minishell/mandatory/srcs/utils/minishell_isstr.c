/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_isstr.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ucho <ucho@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 20:10:48 by ucho              #+#    #+#             */
/*   Updated: 2026/01/29 04:24:40 by ucho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_ispipe(const char *str)
{
	if (!str)
		return (FALSE);
	return (str[0] == '|' && str[1] != '|');
}

int	ft_isboolop(const char *str)
{
	return (!ft_strncmp(str, "&&", 2) || !ft_strncmp(str, "||", 2));
}

int	ft_isparen(const char *str)
{
	return (!ft_strncmp(str, "(", 1) || !ft_strncmp(str, ")", 1));
}

int	ft_isredir(const char *str)
{
	t_idx	i;

	if (!str)
		return (FALSE);
	if (!ft_strncmp(str, ">", 1) || !ft_strncmp(str, ">>", 2)
		|| !ft_strncmp(str, "<", 1) || !ft_strncmp(str, "<<", 2))
		return (TRUE);
	i = 0;
	while (ft_isdigit(str[i]))
		i++;
	if (i > 0 && (!ft_strncmp(&str[i], ">", 1)
			|| !ft_strncmp(&str[i], ">>", 2)
			|| !ft_strncmp(&str[i], "<", 1)
			|| !ft_strncmp(&str[i], "<<", 2)))
	{
		if (i > 10 || ft_atoll(str) > 2147483647)
			return (FALSE);
		return (TRUE);
	}
	return (FALSE);
}
