/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_redir_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ucho <ucho@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 13:01:16 by ucho              #+#    #+#             */
/*   Updated: 2026/01/29 06:47:59 by ucho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

static void	set_redir(t_shell *shell, t_redir *redir, const char **texts);

void	set_redirs(t_shell *shell, t_vec *redirs)
{
	const char	*texts[] = {NULL, NULL, NULL};
	t_idx		i;

	if (!redirs)
		return ;
	i = -1;
	while (++i < redirs->len)
		set_redir(shell, (t_redir *)vec_at(redirs, i), texts);
}

static int	set_fd(t_redir *redir, const char **texts, t_shell *shell)
{
	int	fd;
	int	flag;

	if (ft_strcmp(redir->op, "<") == 0 || ft_strcmp(redir->op, "<<") == 0)
		flag = O_RDONLY;
	else if (ft_strcmp(redir->op, ">") == 0)
		flag = O_WRONLY | O_CREAT | O_TRUNC;
	else
		flag = O_WRONLY | O_CREAT | O_APPEND;
	fd = open(redir->tg.val, flag, 0644);
	if (fd < 0)
	{
		texts[0] = redir->tg.val;
		texts[1] = strerror(errno);
		put_execerr(shell, texts, TRUE);
	}
	return (fd);
}

static void	set_redir(t_shell *shell, t_redir *redir, const char **texts)
{
	int		fd;
	int		target_fd;
	char	*tmp;

	if (redir->tg.err || redir->tg.var)
	{
		texts[0] = redir->tg.val;
		texts[1] = "ambiguous redirect";
		(put_execerr(shell, texts, TRUE), exit(FAILURE));
	}
	fd = set_fd(redir, texts, shell);
	if (fd < 0)
		exit(FAILURE);
	target_fd = redir->fd;
	if (target_fd == NONE)
		target_fd = !(ft_strcmp(redir->op, "<") == 0
				|| ft_strcmp(redir->op, "<<") == 0) * STDOUT + STDIN;
	if (target_fd < 0 || dup2(fd, target_fd) < 0)
	{
		tmp = ft_itoa(redir->fd);
		texts[0] = tmp;
		texts[1] = "Bad file descriptor";
		(put_execerr(shell, texts, TRUE), free(tmp), close(fd), exit(FAILURE));
	}
	close(fd);
}
