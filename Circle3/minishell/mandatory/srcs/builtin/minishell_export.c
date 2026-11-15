/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_export.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ucho <ucho@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 12:47:40 by ucho              #+#    #+#             */
/*   Updated: 2026/01/29 04:27:05 by ucho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int				is_valid_envar(char *str);
static void		put_export(t_shell *shell);
static void		set_env(t_vec *envs, char *str);

int	ft_export(t_shell *shell, char **str)
{
	const char	*texts[] = {"export", NULL, "not a valid identifier", NULL};
	int			code;
	t_idx		i;

	code = SUCCESS;
	if (str[1] == NULL)
		return (put_export(shell), SUCCESS);
	i = 1;
	while (str[i])
	{
		if (!is_valid_envar(str[i]))
		{
			texts[1] = ft_strsjoin((char *[]){"'", str[i], "'", NULL});
			put_execerr(shell, texts, TRUE);
			free((char *)texts[1]);
			code = FAILURE;
		}
		else
			set_env(shell->envs, str[i]);
		i++;
	}
	return (code);
}

static void	put_export(t_shell *shell)
{
	t_env	*env;
	t_idx	i;

	ft_sort(shell->envs, (size_t) &((t_env *)0)->key, TRUE);
	i = 0;
	while (i < shell->envs->len)
	{
		env = (t_env *)vec_at(shell->envs, i);
		if (env && env->key)
		{
			ft_putstrs_fd((char *[]){"declare -x ", env->key, NULL},
				STDOUT);
			if (env->val)
				ft_putstrs_fd((char *[]){"=\"", env->val, "\"", NULL},
					STDOUT);
			ft_putstr_fd("\n", STDOUT);
		}
		i++;
	}
}

static t_env	*get_env(t_vec *envs, const char *key)
{
	t_env	*env;
	t_idx	i;

	i = 0;
	while (i < envs->len)
	{
		env = (t_env *)vec_at(envs, i);
		if (env && env->key && !ft_strcmp(env->key, key))
			return (env);
		i++;
	}
	return (NULL);
}

static void	set_env(t_vec *envs, char *str)
{
	t_env	*env;
	char	*equal;
	char	*key;
	char	*val;

	val = NULL;
	equal = ft_strchr(str, '=');
	if (equal)
	{
		val = ft_strdup(equal + 1);
		key = ft_strndup(str, equal - str);
	}
	else
		key = ft_strdup(str);
	env = get_env(envs, key);
	if (env)
	{
		if (val != NULL)
		{
			free(env->val);
			env->val = val;
		}
		return (free(key));
	}
	vec_push(envs, &(t_env){key, val});
}

int	is_valid_envar(char *str)
{
	if (!str || (!ft_isalpha(str[0]) && str[0] != '_'))
		return (FALSE);
	str++;
	while (*str && *str != '=')
	{
		if (!ft_isalnumbar(*str))
			return (FALSE);
		str++;
	}
	return (TRUE);
}
