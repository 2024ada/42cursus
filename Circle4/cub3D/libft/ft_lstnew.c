/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ucho <ucho@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 11:35:02 by ucho              #+#    #+#             */
/*   Updated: 2026/07/08 13:23:31 by ucho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

t_list	*ft_lstnew(void *data)
{
	t_list	*node;

	node = (t_list *)ft_xmalloc(sizeof(t_list));
	node->data = data;
	node->next = NULL;
	return (node);
}
