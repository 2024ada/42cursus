/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_heredoc.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ucho <ucho@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 12:54:19 by ucho              #+#    #+#             */
/*   Updated: 2026/01/29 04:26:39 by ucho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	cast_heredoc(t_shell *shell, char **raw);
static char	*get_heredoc_name(void);

int	parse_heredoc(t_shell *shell, t_redir *redir)
{
	char		*tmpf;

	tmpf = exec_heredoc(shell, redir, get_heredoc_name());
	if (!tmpf)
		return (FALSE);
	free(redir->op);
	redir->op = ft_strdup("<");
	free_tok(&redir->tg);
	ft_memset(&redir->tg, 0, sizeof(t_tok));
	redir->tg.val = tmpf;
	return (TRUE);
}

char	*exec_heredoc(t_shell *shell, t_redir *redir, char *tmpf)
{
	char	*raw;
	int		fd;

	shell->heredoc = shell->lines;
	fd = open(tmpf, O_WRONLY | O_CREAT | O_TRUNC, 0600);
	if (fd < 0)
		return (perror("heredoc"), free(tmpf), NULL);
	while (TRUE)
	{
		if (get_signal(shell))
			return (close(fd), unlink(tmpf), free(tmpf), NULL);
		raw = get_readline(shell, "> ", TRUE);
		if (get_signal(shell))
			return (free(raw), close(fd), unlink(tmpf), free(tmpf), NULL);
		if (!raw)
			return (put_warning(shell, redir->tg.val), close(fd), tmpf);
		shell->lines++;
		if (!ft_strcmp(raw, redir->tg.val))
			return (free(raw), close(fd), tmpf);
		if (!redir->quote)
			cast_heredoc(shell, &raw);
		(ft_putendl_fd(raw, fd), free(raw));
	}
	return (tmpf);
}

static void	cast_heredoc(t_shell *shell, char **raw)
{
	char	*input;
	char	*buf;
	char	*tok;
	size_t	len;

	input = *raw;
	buf = ft_strdup("");
	while (*input)
	{
		len = ft_strskip(input, ft_isdollar, TRUE) - input;
		if (len)
		{
			tok = ft_substr(input, 0, len);
			(ft_stradd(&buf, tok), free(tok), input += len);
		}
		if (*input == '$')
		{
			len = (size_t)(ft_strskip(input + 1, ft_isalnumbar, FALSE) - input);
			if (*(input + 1) == '?')
				len = 2;
			tok = cast_env(shell, ft_substr(input, 0, len));
			(ft_stradd(&buf, tok), free(tok), input += len);
		}
	}
	(free(*raw), *raw = buf);
}

static char	*get_heredoc_suffix(void)
{
	char	*tty;
	char	*sfx;
	t_idx	i;

	tty = ttyname(STDIN);
	if (!tty)
		return (ft_strdup("no_tty"));
	sfx = ft_strdup(tty);
	i = 0;
	while (sfx[i])
	{
		if (sfx[i] == '/')
			sfx[i] = '_';
		i++;
	}
	return (sfx);
}

static char	*get_heredoc_name(void)
{
	char			*sfx;
	char			*idx;
	char			*name;
	static t_idx	i = 0;

	sfx = get_heredoc_suffix();
	idx = ft_itoa(i++);
	name = ft_strsjoin((char *[]){HEREDOC_DIR, sfx, "_", idx, NULL});
	return (free(idx), free(sfx), name);
}
