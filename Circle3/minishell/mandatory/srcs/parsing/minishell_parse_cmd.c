/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_parse_cmd.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ucho <ucho@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 12:31:16 by ucho              #+#    #+#             */
/*   Updated: 2026/01/29 04:25:05 by ucho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	parse_redir(t_redir *redir, t_tok *tok, char *val);

int	parse_exe(t_cmdline *cmdline, char *tok)
{
	t_glob	glob;
	char	*exe;

	if (!tok)
		return (TRUE);
	if (cmdline->exe)
		return (parse_arg(&cmdline->args, tok));
	ft_memset(&glob, 0, sizeof(t_glob));
	glob.pattern = del_quote(tok, NULL);
	if (!glob.pattern)
		return (TRUE);
	if (!do_glob(&glob, tok))
		return (vec_free(&glob.hits), free(glob.pattern), TRUE);
	exe = glob.pattern;
	if (glob.stat >= 1)
	{
		exe = vec_to_str(&glob.hits, 0, 0, TRUE);
		if (ft_strncmp(glob.pattern, "./", 2) && !ft_strncmp(exe, "./", 2))
			exe += 2;
	}
	cmdline->exe = ft_strdup(exe);
	return (vec_free(&glob.hits), free(glob.pattern), TRUE);
}

int	parse_arg(t_vec *args, char *tok)
{
	t_glob	glob;
	char	*arg;
	t_idx	i;

	ft_memset(&glob, 0, sizeof(t_glob));
	glob.pattern = del_quote(tok, NULL);
	do_glob(&glob, tok);
	if (glob.stat == 0)
		vec_push(args, &glob.pattern);
	else
	{
		i = 0;
		while (i < glob.hits.len)
		{
			arg = vec_to_str(&glob.hits, i, 0, TRUE);
			if (ft_strncmp(glob.pattern, "./", 2) && !ft_strncmp(arg, "./", 2))
				arg += 2;
			arg = ft_strdup(arg);
			vec_push(args, &arg);
			i++;
		}
		free(glob.pattern);
	}
	return (vec_free(&glob.hits), TRUE);
}

int	parse_redirs(t_shell *shell, t_lexer *lexer, t_vec *redirs)
{
	t_redir	redir;
	t_tok	*tok;
	char	*val;

	while (lexer->cur < lexer->toks.len)
	{
		val = ((t_tok *)vec_at(&lexer->toks, lexer->cur))->val;
		if (!ft_isredir(val))
			break ;
		if (lexer->cur + 1 >= lexer->toks.len)
			return (put_tokerr(shell, "newline", FALSE), FALSE);
		tok = (t_tok *)vec_at(&lexer->toks, lexer->cur + 1);
		if (ft_isctrlop(tok->val))
			return (put_tokerr(shell, tok->val, FALSE), FALSE);
		if (ft_isredir(tok->val))
			return (put_tokerr(shell, tok->val, FALSE), FALSE);
		ft_memset(&redir, 0, sizeof(t_redir));
		if (!parse_redir(&redir, tok, val))
			return (FALSE);
		if (!ft_strcmp(redir.op, "<<") && !parse_heredoc(shell, &redir))
			return (free_redir(&redir), FALSE);
		vec_push(redirs, &redir);
		lexer->cur += 2;
	}
	return (TRUE);
}

static int	parse_redir(t_redir *redir, t_tok *tok, char *val)
{
	t_idx	i;

	i = 0;
	while (val[i] && ft_isdigit(val[i]))
		i++;
	redir->fd = NONE;
	if (i > 0)
		redir->fd = ft_atoi(val);
	redir->op = ft_strdup(&val[i]);
	if (tok->var)
		redir->tg.var = ft_strdup(tok->var);
	if (!ft_strncmp(redir->op, "<<", 2))
		redir->tg.val = del_quote(tok->val, &redir->quote);
	else
		redir->tg.val = parse_target(tok->val, &redir->quote, &redir->tg.err);
	return (TRUE);
}

char	*parse_target(const char *tok, int *quote, int *err)
{
	t_glob		glob;
	char		*tg;

	if (!tok)
		return (NULL);
	*quote = (ft_strchr(tok, '\'') != NULL || ft_strchr(tok, '"') != NULL);
	ft_memset(&glob, 0, sizeof(t_glob));
	glob.pattern = del_quote(tok, NULL);
	if (!glob.pattern)
		return (NULL);
	if (!do_glob(&glob, tok))
		return (vec_free(&glob.hits), free(glob.pattern), NULL);
	tg = glob.pattern;
	if (glob.stat == 1)
	{
		tg = vec_to_str(&glob.hits, 0, 0, TRUE);
		if (ft_strncmp(glob.pattern, "./", 2) && !ft_strncmp(tg, "./", 2))
			tg += 2;
	}
	tg = ft_strdup(tg);
	if (glob.stat >= 2)
		*err = TRUE;
	return (vec_free(&glob.hits), free(glob.pattern), tg);
}
