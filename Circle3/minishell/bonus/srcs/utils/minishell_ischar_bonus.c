/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_ischar_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ucho <ucho@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 20:10:48 by ucho              #+#    #+#             */
/*   Updated: 2026/01/29 04:20:19 by ucho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

int	ft_isspace(char c)
{
	return (c == ' ' || c == '\t' || c == '\n');
}

int	ft_isquote(char c)
{
	return (c == '\'' || c == '"');
}

int	ft_isdollar(char c)
{
	return (c == '$');
}

int	ft_isalnumbar(char c)
{
	return (c == '_' || ft_isalnum(c));
}
