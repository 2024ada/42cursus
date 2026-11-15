/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_cast.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ucho <ucho@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 13:03:22 by ucho              #+#    #+#             */
/*   Updated: 2026/01/29 04:26:57 by ucho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*cast_env(t_shell *shell, char *key)
{
	char	*val;

	if (!key)
		return (NULL);
	if (*key != '$' || !*(key + 1))
		return (key);
	if (*(key + 1) == '?')
		val = get_envar(shell, "?");
	else
		val = get_envar(shell, key + 1);
	free(key);
	return (val);
}

char	*get_enval(t_vec *envs, const char *key)
{
	t_env	*env;
	t_idx	i;

	if (!key || !envs)
		return (NULL);
	i = 0;
	while (i < envs->len)
	{
		env = (t_env *)vec_at(envs, i);
		if (env && env->key && ft_strcmp(env->key, key) == 0)
			return (env->val);
		i++;
	}
	return (NULL);
}

char	*get_envar(t_shell *shell, const char *key)
{
	char	*val;

	if (!key || !shell)
		return (NULL);
	if (key[0] == '?' && key[1] == '\0')
	{
		val = ft_itoa(shell->code);
		return (val);
	}
	val = get_enval(shell->envs, key);
	if (val)
		return (ft_strdup(val));
	return (ft_strdup(""));
}
