/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_error.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ucho <ucho@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 12:49:20 by ucho              #+#    #+#             */
/*   Updated: 2026/01/29 04:24:43 by ucho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	put_ansiquote(char *input);

void	put_execerr(t_shell *shell, const char **msg, int is_cmd)
{
	t_idx	i;

	i = 0;
	if (is_cmd)
		ft_putstr_fd(SHELL, STDERR);
	if (is_cmd && !get_shellmode(READ))
	{
		ft_putstr_fd(": line ", STDERR);
		ft_putnbr_fd(shell->lines, STDERR);
	}
	while (msg[i] != NULL)
	{
		if (is_cmd || (is_cmd && !get_shellmode(READ)) || i != 0)
			ft_putstr_fd(": ", STDERR);
		if (!get_shellmode(READ))
			put_ansiquote((char *)msg[i]);
		else
			ft_putstr_fd((char *)msg[i], STDERR);
		i++;
	}
	ft_putendl_fd("", STDERR);
}

static void	put_ansiquote(char *input)
{
	if (ft_strchr(input, '\n'))
	{
		ft_putstr_fd("$'", STDERR);
		while (*input)
		{
			if (*input == '\n')
				ft_putstr_fd("\\n", STDERR);
			else
				ft_putchar_fd(*input, STDERR);
			input++;
		}
		ft_putstr_fd("'", STDERR);
	}
	else
		ft_putstr_fd(input, STDERR);
}

void	put_tokerr(t_shell *shell, const char *tok, int is_eof)
{
	ft_putstr_fd(SHELL, STDERR);
	if (!get_shellmode(READ))
	{
		ft_putstr_fd(": line ", STDERR);
		if (is_eof)
		{
			if (shell->paren)
				ft_putnbr_fd(shell->paren, STDERR);
			else
				ft_putnbr_fd(shell->quote, STDERR);
		}
		else
			ft_putnbr_fd(shell->lines, STDERR);
	}
	if (is_eof)
		ft_putstr_fd(": unexpected EOF while looking for matching ",
			STDERR);
	else
		ft_putstr_fd(": syntax error near unexpected token ", STDERR);
	ft_putstr_fd("`", STDERR);
	ft_putstr_fd((char *)tok, STDERR);
	ft_putendl_fd("'", STDERR);
	shell->code = 2;
	if (!get_shellmode(READ) || is_eof)
		put_syntaxerr(shell, is_eof);
}

void	put_syntaxerr(t_shell *shell, int is_eof)
{
	ft_putstr_fd(SHELL, STDERR);
	if (!get_shellmode(READ))
	{
		ft_putstr_fd(": line ", STDERR);
		if (is_eof)
			ft_putnbr_fd(shell->lines + 1, STDERR);
		else
			ft_putnbr_fd(shell->lines, STDERR);
	}
	if (is_eof)
	{
		ft_putendl_fd(": syntax error: unexpected end of file", STDERR);
		return ;
	}
	ft_putstr_fd(": `", STDERR);
	ft_putstr_fd((char *)shell->input, STDERR);
	ft_putendl_fd("'", STDERR);
}

void	put_warning(t_shell *shell, char *delim)
{
	ft_putstr_fd(SHELL, STDERR);
	if (!get_shellmode(READ))
	{
		ft_putstr_fd(": line ", STDERR);
		ft_putnbr_fd(shell->heredoc, STDERR);
	}
	ft_putstr_fd(": warning: here-document at line ", STDERR);
	ft_putnbr_fd(shell->heredoc, STDERR);
	ft_putstr_fd(" delimited by end-of-file (wanted `", STDERR);
	ft_putstr_fd(delim, STDERR);
	ft_putendl_fd("')", STDERR);
}
