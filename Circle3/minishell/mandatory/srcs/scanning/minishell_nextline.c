/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_nextline.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ucho <ucho@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 18:05:46 by ucho              #+#    #+#             */
/*   Updated: 2026/01/29 04:24:55 by ucho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_buf	*new_buf(t_buf **head, int fd);
static char		*set_nl(char **buf, size_t len);
static char		*set_eof(t_buf **head, t_buf *cur);
static char		*set_err(t_buf **head, t_buf *cur, int fd);

char	*get_nextline(int fd)
{
	static t_buf	*head = NULL;
	t_buf			*node;
	char			*raw;
	char			*tmp;
	int				bytes;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (set_err(&head, NULL, fd));
	node = new_buf(&head, fd);
	raw = (char *)ft_xmalloc(BUFFER_SIZE + 1);
	while (TRUE)
	{
		bytes = read(node->fd, raw, BUFFER_SIZE);
		if (bytes < 0)
			return (free(raw), set_err(&head, node, fd));
		raw[bytes] = '\0';
		ft_stradd(&node->buf, raw);
		tmp = ft_strchr(node->buf, '\n');
		if (tmp)
			return (free(raw), set_nl(&node->buf, tmp - node->buf + 1));
		if (!bytes)
			return (free(raw), set_eof(&head, node));
	}
}

static t_buf	*new_buf(t_buf **head, int fd)
{
	t_buf	*node;
	t_buf	*iter;

	iter = *head;
	while (iter)
	{
		if (iter->fd == fd)
			return (iter);
		iter = iter->next;
	}
	node = ft_xmalloc(sizeof(t_buf));
	node->fd = fd;
	node->buf = NULL;
	node->next = *head;
	*head = node;
	return (node);
}

static char	*set_nl(char **buf, size_t len)
{
	char	*line;
	char	*tmp;

	line = ft_substr(*buf, 0, len);
	tmp = *buf;
	*buf = ft_substr(*buf, len, ft_strlen(*buf) - len);
	free(tmp);
	return (line);
}

static char	*set_eof(t_buf **head, t_buf *node)
{
	char	*line;

	line = NULL;
	if (node->buf && *node->buf)
		line = ft_strdup(node->buf);
	while (*head)
	{
		if (*head == node)
		{
			*head = node->next;
			free(node->buf);
			free(node);
			break ;
		}
		head = &((*head)->next);
	}
	return (line);
}

static char	*set_err(t_buf **head, t_buf *node, int fd)
{
	t_buf	*tmp;

	if (fd == -42)
	{
		while (*head)
		{
			tmp = *head;
			*head = (*head)->next;
			free(tmp->buf);
			free(tmp);
		}
		return (NULL);
	}
	while (node && *head)
	{
		if (*head == node)
		{
			*head = node->next;
			free(node->buf);
			free(node);
			break ;
		}
		head = &((*head)->next);
	}
	return (NULL);
}
