/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_set_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ucho <ucho@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 12:31:16 by ucho              #+#    #+#             */
/*   Updated: 2026/01/29 04:21:03 by ucho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

char		*trim_path(char *path);
static void	set_shellenv(t_vec *envs, const char *path);

int	get_shellmode(int is_tty)
{
	static int	mode = 0;

	if (is_tty >= 0)
		mode = is_tty;
	return (mode);
}

void	set_shell(t_shell *shell, t_lexer *lexer, char *argv, char **envp)
{
	char	*path;
	char	*cwd;

	if (get_shellmode(isatty(STDIN)) && !isatty(STDOUT))
		rl_outstream = stderr;
	set_signal(SIG_IGN, 0, SIGQUIT);
	set_signal(default_handler, 0, SIGINT);
	ft_memset(lexer, 0, sizeof(t_lexer));
	ft_memset(shell, 0, sizeof(t_shell));
	shell->fd = -get_shellmode(READ);
	shell->envs = envp_to_envs(envp);
	if (argv[0] == '/')
		path = trim_path(ft_strdup(argv));
	else
	{
		cwd = getcwd(NULL, 0);
		if (!cwd)
			cwd = ft_strdup(".");
		if (cwd[ft_strlen(cwd) - 1] == '/')
			path = ft_strsjoin((char *[]){cwd, argv, NULL});
		else
			path = ft_strsjoin((char *[]){cwd, "/", argv, NULL});
		(free(cwd), path = trim_path(path));
	}
	(set_shellenv(shell->envs, path), free(path));
}

static void	set_shellenv(t_vec *envs, const char *path)
{
	char		*shlvl_str;
	char		*new_shlvl;
	long long	shlvl;

	if (!envs)
		return ;
	if (del_env(envs, "_"), path)
		add_env(envs, "SHELL", path);
	shlvl_str = get_enval(envs, "SHLVL");
	if (shlvl_str)
	{
		shlvl = ft_atoll(shlvl_str) + 1;
		if (shlvl < 0)
			shlvl = 0;
		else if (shlvl >= 1000)
		{
			ft_putstr_fd(SHELL": warning: shell level (", STDERR);
			ft_putnbr_fd((int)shlvl, STDERR);
			(ft_putendl_fd(") too high, resetting to 1", STDERR), shlvl = 1);
		}
		new_shlvl = ft_lltoa(shlvl);
		(add_env(envs, "SHLVL", new_shlvl), free(new_shlvl));
	}
	else
		add_env(envs, "SHLVL", "1");
}
