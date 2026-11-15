/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_echo.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ucho <ucho@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 12:44:41 by ucho              #+#    #+#             */
/*   Updated: 2026/01/29 04:27:08 by ucho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_option(char *str);

int	ft_echo(char **str)
{
	int		nl;
	t_idx	i;

	nl = TRUE;
	i = 1;
	while (str[i] && is_option(str[i]))
	{
		nl = FALSE;
		i++;
	}
	while (str[i])
	{
		ft_putstr_fd(str[i], STDOUT);
		if (str[i + 1] != NULL)
			ft_putstr_fd(" ", STDOUT);
		i++;
	}
	if (nl)
		ft_putendl_fd("", STDOUT);
	return (SUCCESS);
}

static int	is_option(char *str)
{
	t_idx	i;

	if (str[0] != '-')
		return (FALSE);
	i = 1;
	if (str[i] == '\0')
		return (FALSE);
	while (str[i])
	{
		if (str[i] != 'n')
			return (FALSE);
		i++;
	}
	return (TRUE);
}
