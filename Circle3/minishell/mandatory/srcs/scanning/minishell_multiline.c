/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_multiline.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ucho <ucho@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 13:01:51 by ucho              #+#    #+#             */
/*   Updated: 2026/01/29 04:24:57 by ucho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	set_multiline(t_shell *shell, char *raw)
{
	char	*nl;
	int		pfd[2];

	if (get_shellmode(READ))
	{
		nl = ft_strchr(raw, '\n');
		if (!nl)
			return (FALSE);
		if (pipe(pfd) == -1)
			return (FALSE);
		ft_putstr_fd(nl + 1, pfd[1]);
		close(pfd[1]);
		shell->fd = pfd[0];
		*nl = '\0';
	}
	return (TRUE);
}

void	reset_multiline(t_shell *shell)
{
	if (get_shellmode(READ) && shell->fd >= 0)
	{
		get_nextline(-42);
		close(shell->fd);
		shell->fd = NONE;
	}
}
