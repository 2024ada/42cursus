/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ucho <ucho@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 12:31:16 by ucho              #+#    #+#             */
/*   Updated: 2026/01/29 04:21:11 by ucho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

volatile sig_atomic_t	g_sig;

int	main(int argc, char **argv, char **envp)
{
	t_lexer	lexer;
	t_shell	shell;

	(void)argc;
	set_shell(&shell, &lexer, argv[0], envp);
	run_shell(&shell, &lexer);
	return (shell.code);
}
