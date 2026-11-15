/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   000_get_nextline.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ucho <ucho@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/09 04:47:45 by ucho              #+#    #+#             */
/*   Updated: 2026/07/09 04:47:46 by ucho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

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
			return (put_err("INPUT", "Cannot read map(.cub) file"),
				free(raw), set_err(&head, node, fd));
		raw[bytes] = '\0';
		ft_stradd(&node->buf, raw);
		tmp = ft_strchr(node->buf, '\n');
		if (tmp)
			return (free(raw), set_nl(&node->buf, tmp - node->buf + 1));
		if (!bytes)
			return (free(raw), set_eof(&head, node));
	}
}
