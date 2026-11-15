/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_reset_pipex.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ucho <ucho@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 18:24:18 by ucho              #+#    #+#             */
/*   Updated: 2026/01/29 04:26:48 by ucho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		set_redirs(t_shell *shell, t_vec *redirs);
static int	put_sigerrs(t_shell *shell, t_vec *cmdlines,
				pid_t *pids, int *stats);

int	reset_pipex(t_shell *shell, t_vec *cmdlines, pid_t *pids, int *stats)
{
	int		stat;
	t_idx	i;

	i = -1;
	while (++i < cmdlines->len)
	{
		if (WIFSIGNALED(stats[i]) && WTERMSIG(stats[i]) == SIGINT)
		{
			ft_putendl_fd("", STDOUT);
			break ;
		}
	}
	set_signal(SIG_DFL, 0, SIGINT);
	stat = stats[cmdlines->len - 1];
	if (WIFSIGNALED(stat))
		return (put_sigerrs(shell, cmdlines, pids, stats));
	if (WIFEXITED(stat))
		return (free(pids), free(stats), WEXITSTATUS(stat));
	return (free(pids), free(stats), 1);
}

static void	put_sigerr(int *info, size_t idx, int *mask)
{
	int			state;
	const char	*msg[] = {"       ", " Quit    ", " Done    ", " Exit ", NULL};

	state = (WIFSIGNALED(info[0]) && (WTERMSIG(info[0]) == SIGQUIT))
		| ((WIFEXITED(info[0]) && WEXITSTATUS(info[0]) == 0) << 1)
		| ((WIFEXITED(info[0]) && WEXITSTATUS(info[0]) != 0) * 3);
	if (idx == 0)
	{
		(ft_putstr_fd(SHELL": line ", STDERR), ft_putnbr_fd(info[1], STDERR));
		(ft_putstr_fd(": ", STDERR), *mask = state);
	}
	else
		ft_putstr_fd("     ", STDERR);
	ft_putnbr_fd(info[2], STDERR);
	if (idx == 0)
		ft_putstr_fd((char *)msg[*mask], STDERR);
	else
		ft_putstr_fd((char *)msg[state * (state != *mask)], STDERR);
	if (WIFEXITED(info[0]) && WEXITSTATUS(info[0]))
		ft_putnbr_fd(WEXITSTATUS(info[0]), STDERR);
	ft_putstr_fd("                ", STDERR);
	if (WIFSIGNALED(info[0]) && WCOREDUMP(info[0]))
		ft_putstr_fd("(core dumped) ", STDERR);
	if (idx != 0)
		ft_putstr_fd("| ", STDERR);
}

static int	put_sigerrs(t_shell *shell, t_vec *cmdlines,
							pid_t *pids, int *stats)
{
	char	*cmd;
	int		mask;
	t_idx	i;
	int		last;

	last = stats[cmdlines->len - 1];
	shell->code = 128 + WTERMSIG(last);
	if (get_shellmode(READ) && WTERMSIG(last) == SIGQUIT)
	{
		ft_putstr_fd("Quit", STDERR);
		if (WCOREDUMP(last))
			ft_putstr_fd(" (core dumped)", STDERR);
		ft_putendl_fd("", STDERR);
	}
	else if (!get_shellmode(READ) && WTERMSIG(last) != SIGINT)
	{
		TRUE && (i = -1, mask = 0);
		while (++i < cmdlines->len)
		{
			cmd = node_to_str(*(t_node **)vec_at(cmdlines, i));
			put_sigerr((int []){stats[i], shell->lines, pids[i]}, i, &mask);
			(ft_putendl_fd(cmd, STDERR), free(cmd));
		}
	}
	return (free(pids), free(stats), shell->code);
}
