/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   function02-1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ucho <ucho@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 15:11:17 by ucho              #+#    #+#             */
/*   Updated: 2025/08/19 11:43:03 by ucho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	is_valid_input(char *name)
{
	size_t	len;

	len = ft_strlen(name);
	if (len < 5)
		return (0);
	return (ft_strncmp(name + len - 4, ".fdf", 4) == 0);
}

int	set_input(char *name)
{
	int	input;

	input = open(name, O_RDONLY);
	if (input < 0)
	{
		perror("Error");
		exit(EXIT_FAILURE);
	}
	if (!is_valid_input(name))
	{
		close(input);
		put_error("Error: Invalid file extension\nUsage: ./fdf <map.fdf>\n");
		exit(EXIT_FAILURE);
	}
	return (input);
}
