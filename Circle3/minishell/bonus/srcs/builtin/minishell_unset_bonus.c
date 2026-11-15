/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_unset_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ucho <ucho@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 12:31:16 by ucho              #+#    #+#             */
/*   Updated: 2026/01/29 04:23:37 by ucho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

int		is_valid_envar(char *str);

int	ft_unset(t_shell *shell, char **str)
{
	int		code;
	t_idx	i;

	code = SUCCESS;
	if (str[1] == NULL)
		return (SUCCESS);
	i = 1;
	while (str[i])
	{
		if (is_valid_envar(str[i]))
			del_env(shell->envs, str[i]);
		i++;
	}
	return (code);
}
