/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_envs_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ucho <ucho@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 13:05:05 by ucho              #+#    #+#             */
/*   Updated: 2026/01/29 04:23:29 by ucho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

t_vec	*envp_to_envs(char **envp)
{
	t_vec	*envs;
	t_env	env;
	char	*equal;
	t_idx	i;

	if (!envp)
		exit(FAILURE);
	envs = (t_vec *)ft_xmalloc(sizeof(t_vec));
	vec_init(envs, sizeof(t_env), 16, free_env);
	i = -1;
	while (envp[++i])
	{
		equal = ft_strchr(envp[i], '=');
		if (!equal)
			continue ;
		env.key = ft_substr(envp[i], 0, equal - envp[i]);
		env.val = ft_strdup(equal + 1);
		if (!env.key || !env.val)
		{
			(free(env.key), free(env.val));
			continue ;
		}
		vec_push(envs, &env);
	}
	return (envs);
}

char	**envs_to_envp(t_vec *envs)
{
	char	**envp;
	t_env	*env;
	char	*val;
	t_idx	i;
	t_idx	j;

	if (!envs)
		return (NULL);
	envp = (char **)ft_xmalloc(sizeof(char *) * (envs->len + 1));
	i = 0;
	j = 0;
	while (i < envs->len)
	{
		env = (t_env *)vec_at(envs, i);
		i++;
		if (!env || !env->key || !env->val)
			continue ;
		val = ft_strsjoin((char *[]){env->key, "=", env->val, NULL});
		envp[j++] = val;
	}
	envp[j] = NULL;
	return (envp);
}

void	add_env(t_vec *envs, const char *key, const char *val)
{
	t_env	*env;
	t_idx	i;

	if (!envs || !key || !val)
		return ;
	i = 0;
	while (i < envs->len)
	{
		env = (t_env *)vec_at(envs, i);
		if (env && env->key && ft_strcmp(env->key, key) == 0)
		{
			free(env->val);
			env->val = ft_strdup(val);
			return ;
		}
		i++;
	}
	vec_push(envs, &(t_env){ft_strdup(key), ft_strdup(val)});
}

void	del_env(t_vec *envs, const char *key)
{
	t_env	*env;
	t_idx	i;

	if (!envs || !key)
		return ;
	i = 0;
	while (i < envs->len)
	{
		env = (t_env *)vec_at(envs, i);
		if (env && env->key && ft_strcmp(env->key, key) == 0)
		{
			free(env->key);
			free(env->val);
			ft_memmove((char *)envs->data + (i * envs->size),
				(char *)envs->data + ((i + 1) * envs->size),
				(envs->len - i - 1) * envs->size);
			envs->len--;
			return ;
		}
		i++;
	}
}

void	free_env(void *elem)
{
	t_env	*env;

	if (!elem)
		return ;
	env = (t_env *)elem;
	free(env->key);
	free(env->val);
}
