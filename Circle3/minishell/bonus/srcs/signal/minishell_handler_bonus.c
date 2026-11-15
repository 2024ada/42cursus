/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_handler_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ucho <ucho@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 12:31:16 by ucho              #+#    #+#             */
/*   Updated: 2026/01/29 04:20:30 by ucho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

void	default_handler(int signo)
{
	(void)signo;
	g_sig = SIGINT;
	if (!get_shellmode(READ))
		exit(130);
}

void	prompt_handler(int signo)
{
	(void)signo;
	g_sig = SIGINT;
	if (!get_shellmode(READ))
		exit(130);
	ft_putendl_fd("", STDOUT);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void	heredoc_handler(int signo)
{
	(void)signo;
	g_sig = SIGINT;
	if (!get_shellmode(READ))
		exit(130);
	ft_putendl_fd("", STDOUT);
	rl_replace_line("", 0);
	rl_on_new_line();
}

t_handler	get_handler(int type)
{
	static t_handler	handlers[] = {
		prompt_handler,
		heredoc_handler
	};

	return (handlers[type]);
}
