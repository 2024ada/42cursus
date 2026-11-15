/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_env.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ucho <ucho@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 12:46:52 by ucho              #+#    #+#             */
/*   Updated: 2026/01/29 04:27:07 by ucho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_env(t_shell *shell, char **str)
{
	t_env	*envs;
	t_idx	i;

	if (str[1] != NULL)
	{
		ft_putstr_fd("env: too many arguments\n", STDERR);
		return (FAILURE);
	}
	i = 0;
	while (i < shell->envs->len)
	{
		envs = (t_env *)vec_at(shell->envs, i);
		if (envs && envs->key && envs->val)
			ft_putstrs_fd((char *[]){envs->key, "=", envs->val, "\n", NULL},
				STDOUT);
		i++;
	}
	return (SUCCESS);
}
