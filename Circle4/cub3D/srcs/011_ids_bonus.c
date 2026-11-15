/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   030_ids_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ucho <ucho@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/09 04:49:13 by ucho              #+#    #+#             */
/*   Updated: 2026/07/09 04:49:13 by ucho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D_bonus.h>

#ifdef BONUS

const char	**required_ids(void)
{
	static const char	*ids[] = {
		"NO",
		"SO",
		"WE",
		"EA",
		"F",
		"C",
		"T",
		"P",
		"P_D",
		"H",
		"G",
		"Da",
		"I_M",
		"P_Aa",
		"I_Ha",
		"I_Aa",
		"Ma_F",
		"Ma_B",
		"Ma_L",
		"Ma_R",
		"Ma_D",
		"Ma_A", NULL};

	return (ids);
}

const char	*optional_ids(void)
{
	static char	ids[27] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	static int	init = FALSE;
	t_idx		remove[26];
	t_idx		i;
	t_idx		j;

	if (!init)
	{
		ft_bzero(remove, sizeof(remove));
		i = 0;
		while (required_ids()[i])
			remove[required_ids()[i++][0] - 'A'] = 1;
		j = 0;
		i = 0;
		while (ids[i])
		{
			if (!remove[ids[i] - 'A'])
				ids[j++] = ids[i];
			i++;
		}
		ids[j] = '\0';
		init = TRUE;
	}
	return (ids);
}

#endif
