/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_widgets04_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ucho <ucho@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 02:08:00 by ucho              #+#    #+#             */
/*   Updated: 2025/08/19 14:14:40 by ucho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

const char	**widget16(void)
{
	static const char	*xpm[] = {
		"68 14 5 1 ",
		"  c #1E212A",
		". c #566681",
		"X c #D2D3CF",
		"o c #2D232B",
		"O c #474B59",
		"                        XXX                    XXX                  ",
		"OXXXXXXo               OXXX                    XXXo                 ",
		"OXXXXXXXo                                 .XXO                      ",
		"OXXX .XX.                                 .XXO                      ",
		"OXXX .XXXXXXXX. .XXXXo  XXX  XXXXX   .XXXXXXXXXXXX  OXXXXX  XXXXXXX ",
		"OXXXXXXXoXXXXX.XXXXXXXO XXX XXXXXXX .XXXXXXXXXXXXX .XXXXXXX XXXXXXXO",
		"OXXXXXXO XXXO .XXX .XXX XXX.XXX .XX.XXX OO.XXO XXX XXXO XXXOXXXo.XX.",
		"OXXX     XXX  .XX.  XXX XXX.XXXXXXX.XXX   .XXO XXX XXX  .XX.XXX .XX.",
		"OXXX     XXX  .XXX .XXX XXX.XX.    OXXX OO.XXO XXX XXXO XXXOXXX .XX.",
		"OXXX     XXX   XXXXXXXO XXX XXXXXXXo.XXXXX.XXO XXX .XXXXXXX XXX .XX.",
		"OXXX     XXX    .XXXXo  XXX  XXXXXo  .XXXX.XXO XXX  OXXXXX  XXX .XX.",
		"                        XXX                                         ",
		"                        XXX                                         ",
		"                        XXX                                         ",
		NULL};

	return (xpm);
}

const char	**widget17(void)
{
	static const char	*xpm[] = {
		"49 14 5 1 ",
		"  c #1E212A",
		". c #566681",
		"X c #D2D3CF",
		"o c #2D232B",
		"O c #474B59",
		"                        .XXo.XXO                 ",
		"  XXXXX                 .XXo.XX.                 ",
		" XXXXXXX                .XXo                     ",
		".XXX .X                 .XXo                     ",
		".XXXO     XXXX. .XXXXXXO.XXo.XXO.XXXXXX   XXXXXXX",
		" XXXXXX  XXXXX..XXXXXXXO.XXo.XXO.XXXXXXX XXXXXXXX",
		"   XXXXX.XXX OOXXXO XXXO.XXo.XXO.XX.OXXX.XXX .XXX",
		"    OXXX.XX.   XXX  .XXO.XXo.XXO.XXo XXX.XX.  XXX",
		" XX OXXX.XXX OOXXXO XXXO.XXo.XXO.XXo XXX.XXX .XXX",
		"XXXXXXX. XXXXX..XXXXXXXO.XXo.XXO.XXo XXX XXXXXXXX",
		" .XXXX.   XXXX. .XXXXXXO.XXo.XXO.XXo XXX  XXXXXXX",
		"                                        .XXX .XXX",
		"                                         XXXXXXXO",
		"                                          XXXXXO ",
		NULL};

	return (xpm);
}

const char	**widget18(void)
{
	static const char	*xpm[] = {
		"76 11 5 1 ",
		"  c #1E212A",
		". c #566681",
		"X c #D2D3CF",
		"o c #2D232B",
		"O c #474B59",
		"                                      .XXo             .XX.          "
		"       ", "OXXXXXXXo                             .XXo             .XX"
		"X                 ", "OXXXXXXXo                             .XXo     "
		"    XXX                      ", "   XXX                              "
		"  .XXo         XXX                      ", "   XXX  .XXXXX .XXXXXXO.X"
		"XXXXX  .XXXXO.XXo XXXXXXX.XXXX.XX.  .XXXXo .XXXXXXo", "   XXX  .XXXXX"
		".XXXXXXXO.XXXXXXX XXXXXO.XXoXXXXXXXX.XXXX.XX. XXXXXXXO.XXXXXXX", "   "
		"XXX  .XXX  XXXO XXXO.XX.OXXXOXXXO  .XX.XXX OXXX XXX .XX..XXX .XXX.XXX"
		" XXX", "   XXX  .XXO  XXX  .XXO.XXo XXX .XXXXO.XX.XXX  XXX XXX .XX..X"
		"X.  XXX.XXO XXX", "   XXX  .XXO  XXXO XXXO.XXo XXX   OXXX.XX.XXX OXXX"
		" XXX .XX..XXX .XXX.XXO XXX", "   XXX  .XXO  .XXXXXXXO.XXo XXX XXXXX.."
		"XXoXXXXXXXX XXX .XX. XXXXXXXO.XXO XXX", "   XXX  .XXO   .XXXXXXO.XXo "
		"XXX.XXXXX .XXo XXXXXXX XXX .XX.  .XXXXo .XXO XXX", NULL};

	return (xpm);
}

const char	**widget19(void)
{
	static const char	*xpm[] = {
		"57 11 5 1 ",
		"  c #1E212A",
		". c #566681",
		"X c #D2D3CF",
		"o c #474B59",
		"O c #2D232B",
		"                                    .XX.                 ",
		"oXXXXXXO                            .XXX                 ",
		"oXXXXXXXO         .XXo          XXX                      ",
		"oXXX XXXo         .XXo          XXX                      ",
		"oXXX XXXo  XXXXX oXXXXX XXXXXXX.XXXX.XX.  XXXXX  .XXXXXXO",
		"oXXXXXXX oXXXXXXXoXXXXXXXXXXXXX.XXXX.XX.oXXXXXXX .XXXXXXX",
		"oXXXXXo  .XX. .XX..XXooXXX oXXX XXX .XX..XX. .XX..XXX XXX",
		"oXXXXXX  XXXO oXXX.XXo.XXX  XXX XXX .XX.XXXO oXXX.XXo XXX",
		"oXXX.XXX .XX. .XX..XXooXXX oXXX XXX .XX..XX. .XX..XXo XXX",
		"oXXXoXXXooXXXXXXX .XXo XXXXXXXX XXX .XX.oXXXXXXX .XXo XXX",
		"oXXX .XXXo XXXXX  .XXo  XXXXXXX XXX .XX.  XXXXX  .XXo XXX", NULL};

	return (xpm);
}

const char	**widget20(void)
{
	static const char	*xpm[] = {
		"54 13 5 1 ",
		"  c #1E212A",
		". c #566681",
		"X c #D2D3CF",
		"o c #474B59",
		"O c #2D232B",
		"   XXXXX                                              ",
		" .XXXXXXX                  .XXo                       ",
		" XXXX  .X                  .XXo                       ",
		".XXX      .XXXXXX..XXXXXXOoXXXXXXXX .XX..XXXXX .XXXXo ",
		".XXo     .XXXXXXX..XXXXXXX.XXXXXXXX .XX..XXXXX.XXXXXXo",
		".XXo     .XX. .XX..XXX .XXX.XXo XXX .XX..XXX  XXXO XXX",
		".XXX     XXXO .XX..XXO oXXX.XXo XXX .XX..XXo  XXXXXXXX",
		" XXXX  .X.XX. .XX..XXX .XXX.XXo XXX .XX..XXo  XXX     ",
		" .XXXXXXX.XXXXXXX..XXXXXXXO.XXo XXXXXXXo.XXo  .XXXXXXX",
		"   XXXXX  .XXXXXX..XXXXXXo .XXo  XXXXXo .XXo   .XXXXX ",
		"                  .XXo                                ",
		"                  .XXo                                ",
		"                  .XXo                                ", NULL};

	return (xpm);
}
