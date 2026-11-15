/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_debug_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ucho <ucho@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 18:31:23 by ucho              #+#    #+#             */
/*   Updated: 2026/01/29 04:23:34 by ucho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

static char	*prompt_to_str(t_prompt *prompt);
static char	*cmdline_to_str(t_cmdline *cmdline);

char	*node_to_str(t_node *node)
{
	char		*str;
	char		*prompt;

	if (node && node->kind == K_CMDLINE)
		return (cmdline_to_str((t_cmdline *)node->data));
	if (node && node->kind == K_SUBSHELL)
	{
		node = (t_node *)((t_subshell *)node->data)->prompt;
		if (node && node->kind == K_PROMPT)
			prompt = prompt_to_str((t_prompt *)node->data);
		else
			prompt = ft_strdup("");
		str = ft_strsjoin((char *[]){"( ", prompt, " )", NULL});
		free(prompt);
		return (str);
	}
	return (ft_strdup(""));
}

static char	*cmdline_to_str(t_cmdline *cmdline)
{
	char	*str;
	char	*arg;
	t_idx	i;

	str = NULL;
	if (cmdline->exe)
		ft_stradd(&str, cmdline->exe);
	i = 0;
	while (i < cmdline->args.len)
	{
		arg = *(char **)vec_at(&cmdline->args, i);
		if (arg)
		{
			ft_stradd(&str, " ");
			ft_stradd(&str, arg);
		}
		i++;
	}
	if (!str)
		str = ft_strdup("");
	return (str);
}

static char	*pipeline_to_str(t_pipeline *pipeline)
{
	char	*str;
	char	*node;
	t_idx	i;

	str = NULL;
	i = 0;
	while (i < pipeline->cmdlines.len)
	{
		node = node_to_str(*(t_node **)vec_at(&pipeline->cmdlines, i));
		if (node)
		{
			ft_stradd(&str, node);
			free(node);
		}
		if (i < pipeline->cmdlines.len - 1)
			ft_stradd(&str, " | ");
		i++;
	}
	if (!str)
		str = ft_strdup("");
	return (str);
}

static char	*prompt_to_str(t_prompt *prompt)
{
	char		*str;
	char		*pipeline;
	char		*op;
	t_idx		i;

	str = NULL;
	i = 0;
	while (i < prompt->pipelines.len)
	{
		pipeline = pipeline_to_str((t_pipeline *)vec_at(&prompt->pipelines, i));
		ft_stradd(&str, pipeline);
		free(pipeline);
		if (i < prompt->ops.len)
		{
			op = *(char **)vec_at(&prompt->ops, i);
			ft_stradd(&str, " ");
			ft_stradd(&str, op);
			ft_stradd(&str, " ");
		}
		i++;
	}
	if (!str)
		str = ft_strdup("");
	return (str);
}
