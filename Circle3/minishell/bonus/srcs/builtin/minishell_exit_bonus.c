/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_exit_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ucho <ucho@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 12:48:02 by ucho              #+#    #+#             */
/*   Updated: 2026/01/29 04:23:42 by ucho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

static int	is_valid_code(char *str);

int	ft_exit(t_shell *shell, char **str, int is_called)
{
	const char	*texts[] = {"exit", NULL, NULL, NULL};

	if (is_called)
		ft_putstr_fd("exit\n", STDERR);
	if (str[1] == NULL)
		exit(shell->code);
	else if (is_valid_code(str[1]) == FALSE)
	{
		texts[1] = str[1];
		texts[2] = "numeric argument required";
		(put_execerr(shell, texts, TRUE), exit(MISUSE));
	}
	else if (str[2] != NULL)
	{
		texts[1] = "too many arguments";
		return (put_execerr(shell, texts, TRUE), FAILURE);
	}
	else
		exit((unsigned char)ft_atoll(str[1]));
}

static int	is_valid_code(char *str)
{
	char	*num;
	char	*limit;
	int		len;

	if (!str || !*str)
		return (FALSE);
	limit = "9223372036854775807";
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			limit = "9223372036854775808";
		str++;
	}
	if (!*str)
		return (FALSE);
	num = str;
	len = 0;
	while (*str && ft_isdigit(*str))
	{
		len++;
		str++;
	}
	if (*str || len > 19 || (len == 19 && ft_strcmp(num, limit) > 0))
		return (FALSE);
	return (TRUE);
}
