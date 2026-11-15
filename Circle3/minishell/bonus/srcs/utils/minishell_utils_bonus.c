/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ucho <ucho@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 13:02:06 by ucho              #+#    #+#             */
/*   Updated: 2026/01/29 04:20:15 by ucho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

int	ft_isctrlop(const char *str)
{
	return (ft_isparen(str) || ft_ispipe(str) || ft_isboolop(str));
}

int	ft_isop(const char *str)
{
	return (ft_isredir(str) || ft_isctrlop(str));
}

int	ft_issep(const char *str)
{
	return (ft_isspace(str[0]) || ft_isop(str));
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

const char	*get_op(const char *str, int op)
{
	const char	*double_ops[] = {"&&", "||", ">>", "<<", NULL};
	const char	*single_ops[] = {"|", ">", "<", "(", ")", NULL};
	char		**ops;
	t_idx		i;

	i = 0;
	if (op == DOUBLE)
		ops = (char **)double_ops;
	else if (op == SINGLE)
		ops = (char **)single_ops;
	else
		return (NULL);
	while (ops[i])
	{
		if (!ft_strncmp(str, ops[i], ft_strlen(ops[i])))
			return (ops[i]);
		i++;
	}
	return (NULL);
}
