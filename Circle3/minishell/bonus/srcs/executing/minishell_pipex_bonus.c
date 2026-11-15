/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_pipex_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ucho <ucho@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 18:17:50 by ucho              #+#    #+#             */
/*   Updated: 2026/01/29 04:23:20 by ucho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

int	pipex(t_shell *shell, t_vec *cmdlines)
{
	pid_t	*pids;
	int		*stats;
	t_idx	i;

	pids = ft_xmalloc(sizeof(pid_t) * cmdlines->len);
	stats = ft_xmalloc(sizeof(int) * cmdlines->len);
	run_pipex(shell, cmdlines, pids);
	set_signal(SIG_IGN, 0, SIGINT);
	i = -1;
	while (++i < cmdlines->len)
		if (pids[i] > 0)
			waitpid(pids[i], &stats[i], 0);
	return (reset_pipex(shell, cmdlines, pids, stats));
}
