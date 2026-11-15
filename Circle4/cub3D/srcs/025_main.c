/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   014_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ucho <ucho@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/09 04:48:33 by ucho              #+#    #+#             */
/*   Updated: 2026/07/09 04:48:33 by ucho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

int	main(int argc, char **argv)
{
	t_app		app;

	open_app(argc, argv, &app);
	init_app(&app, &app.core.games[0]);
	rend_app(&app, &app.core.games[0]);
	exec_app(&app);
	return (0);
}
