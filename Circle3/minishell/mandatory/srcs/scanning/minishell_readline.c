/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_readline.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ucho <ucho@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 19:05:04 by ucho              #+#    #+#             */
/*   Updated: 2026/01/29 05:57:01 by ucho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*ft_readline(const char *prompt, int is_secondary);

char	*get_readline(t_shell *shell, const char *prompt, int is_secondary)
{
	char	*line;
	size_t	len;

	set_signal(get_handler(is_secondary), SA_RESTART, SIGINT);
	if (shell->fd >= 0)
	{
		line = get_nextline(shell->fd);
		if (line)
		{
			len = ft_strlen(line);
			if (len > 0 && line[len - 1] == '\n')
				line[len - 1] = '\0';
			set_signal(default_handler, 0, SIGINT);
			return (line);
		}
		reset_multiline(shell);
	}
	line = ft_readline((char *)prompt, is_secondary);
	set_signal(default_handler, 0, SIGINT);
	return (line);
}

static int	get_curpos(char *buf, int *row, int *col)
{
	char	*sep;

	if (buf[0] != '\033' || buf[1] != '[')
		return (FALSE);
	sep = ft_strchr(buf, ';');
	if (!sep)
		return (FALSE);
	*row = ft_atoi(buf + 2);
	*col = ft_atoi(sep + 1);
	return (TRUE);
}

static char	*keep_eol(char *prompt)
{
	char			buf[32];
	int				pos[2];
	struct termios	old;
	struct termios	new;
	t_idx			i;

	tcgetattr(STDIN, &old);
	new = old;
	new.c_lflag &= ~(ICANON | ECHO);
	tcsetattr(STDIN, TCSANOW, &new);
	ft_putstr_fd("\033[6n", STDOUT);
	i = 0;
	while (i < 31 && read(STDIN, &buf[i], 1) == 1)
		if (buf[i++] == 'R')
			break ;
	buf[i] = '\0';
	tcsetattr(STDIN, TCSANOW, &old);
	if (get_curpos(buf, &pos[0], &pos[1]) && pos[1] > 1)
		prompt += 6;
	return (prompt);
}

static int	reset_ps2(void)
{
	if (g_sig == SIGINT)
		rl_done = 1;
	return (0);
}

static char	*ft_readline(const char *prompt, int is_secondary)
{
	char	*line;

	if (!get_shellmode(READ))
		return (NULL);
	if (!is_secondary && isatty(STDIN) && isatty(STDOUT))
		prompt = (char *)keep_eol((char *)prompt);
	if (is_secondary)
		rl_event_hook = reset_ps2;
	line = readline(prompt);
	rl_event_hook = NULL;
	return (line);
}
