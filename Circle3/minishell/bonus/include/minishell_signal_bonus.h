/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_signal_bonus.h                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ucho <ucho@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 00:00:00 by ucho              #+#    #+#             */
/*   Updated: 2026/01/29 04:23:57 by ucho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_SIGNAL_BONUS_H
# define MINISHELL_SIGNAL_BONUS_H

extern volatile sig_atomic_t	g_sig;

typedef struct s_shell			t_shell;

typedef void					(*t_handler)(int);

void		set_signal(void (*handler)(int), int flag, int sig);
int			get_signal(t_shell *shell);

t_handler	get_handler(int type);
void		default_handler(int signo);

#endif
