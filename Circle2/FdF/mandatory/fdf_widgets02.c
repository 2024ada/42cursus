/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   widgets02.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ucho <ucho@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 02:08:00 by ucho              #+#    #+#             */
/*   Updated: 2025/06/21 19:28:13 by ucho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

const char	**widget09(void)
{
	static const char	*xpm[] = {"29 32 5 1 ", "  c #FEFEFE", ". c #898A9A",
		"X c #515567", "o c #E8F4E9", "O c #C9CFC6",
		"             .X.o            ", "             OX.             ",
		"            Oo  o            ", "          o.XXXXX.o          ",
		"        o.XXXXXXXXX.o        ", "       oXXX.o   o.XXXo       ",
		"      OXX.o       o.XXO      ", "     o.X.           .X.o     ",
		"     OX.o           o.X.     ", "    o.XO             OXXo    ",
		"    OXXo             o.XO    ", "    OX.               .XO    ",
		"    OX.               OX.    ", "    OX.               OX.    ",
		"    OX.               OX.    ", "    .XO               OX.    ",
		"    .XO               OX.    ", "   o.XO               OX.o   ",
		"   oXXo               oXXo   ", "   OX.                 .XO   ",
		"   .XO                 OX.   ", "  OXXo                 o.XO  ",
		" OXXO                   OXXO ", "oXX.                     OXXo",
		"OX.                       .XO", "OX.                       .X.",
		"oXXXXXXXXXXXXXXXXXXXXXXXXXXXo", " OXXXXXXXXXXXXXXXXXXXXXXXXXO ",
		"          OX.   .X.          ", "          OXXO OXXO          ",
		"           .XXXXX.           ", "            OXXXO            ",
		NULL};

	return (xpm);
}

const char	**widget10(void)
{
	static const char	*xpm[] = {"23 23 3 1 ", "X c #D6D2D0", ". c #D6D3D1",
		"  c None", "        XX...XX        ", "      X.........X      ",
		"    X.............X    ",
		"   X...............X   ",
		"  X.................X  ",
		"  ...................  ",
		" X...................X ",
		" X.................... ",
		"X.....................X",
		".......................",
		".......................",
		".......................",
		".......................",
		"......................X",
		"X.....................X",
		" ..................... ",
		" X...................X ",
		"  ...................  ",
		"  X.................X  ",
		"   X...............X   ",
		"     .............     ",
		"      X.........X      ",
		"        XX...XX        ", NULL};

	return (xpm);
}

const char	**widget11(void)
{
	static const char	*xpm[] = {"23 23 2 1 ", ". c #EF4444", "  c None",
		"        .......        ", "      ...........      ",
		"    ...............    ",
		"   .................   ",
		"  ...................  ",
		"  ...................  ",
		" ..................... ",
		" ..................... ",
		".......................",
		".......................",
		".......................",
		".......................",
		".......................",
		".......................",
		".......................",
		" ..................... ",
		" ..................... ",
		"  ...................  ",
		"  ...................  ",
		"   .................   ",
		"    ...............    ",
		"      ...........      ",
		"        .......        ", NULL};

	return (xpm);
}

const char	**widget12(void)
{
	static const char	*xpm[] = {
		"44 15 5 1 ",
		"  c #FEFEFE",
		". c #EFFADC",
		"X c #676668",
		"o c #CBD0C8",
		"O c #847E90",
		"                    .XXXo                   ",
		"                    .XXXo                   ",
		"                    .XXXo                   ",
		"                    .XXXo                   ",
		"                    .XXXo                   ",
		"XXO.  oXXO   .OXXXO .XXXoOXXOo     oXXXXO   ",
		"XXO.  oXXO  .XXXXXXo.XXXXXXXXXo  .OXXXXXXXo ",
		"XXO.  oXXO  OXXXXXXo.XXXXXXXXXo  OXXXXXXXXO ",
		"XXO.  oXXO oXXXo  o..XXXO .OXXO .XXXo  oXXXo",
		"XXO.  oXXO oXXO     .XXXo  oXXO oXXO    oXXo",
		"XXX.  oXXO oXXO     .XXXo  oXXO oXXO    oXXo",
		"XXXo .OXXO oXXXo  o..XXXo  oXXO .XXXo  oXXXo",
		"OXXXXXXXXo  OXXXXXXo.XXXo  oXXO  OXXXXXXXXO ",
		".XXXXXXXO   .XXXXXXo.XXXo  oXXO  .OXXXXXXXo ",
		" .OXXXXo     .OXXXO .XXXo  oXXO    oXXXXO   ", NULL};

	return (xpm);
}

const char	**widget13(void)
{
	static const char	*xpm[] = {
		"44 15 4 1 ",
		"  c #FDFBF8",
		". c #26C2CD",
		"X c #02BABC",
		"o c #98E4ED",
		"                     .XXo                   ",
		"                     .XXo                   ",
		"                     .XXo                   ",
		"                     .XXo                   ",
		"                     .XXo                   ",
		".XXo   XXX    o.XX.  .XXooXXXo     o.XXX.   ",
		".XXo   XXX   .XXXXXo .XXXXXXXXo   .XXXXXXXo ",
		".XXo   XXX  oXXXXXXo .XXXXXXXX.  oXXXXXXXXXo",
		".XXo   XXX  .XX.   o .XX.  oXXX  .XX.   .XXo",
		".XXo   XXX  XXX      .XXo   XXX  XXX    oXX.",
		".XXo   XXX  XXX      .XXo   XXX  XXX    oXX.",
		".XX.  oXX.  XXX.   o .XXo   XXX  .XX.   .XXo",
		"oXXXXXXXX.  oXXXXXXo .XXo   XXX  oXXXXXXXXXo",
		" .XXXXXXX    .XXXXXo .XXo   XXX   .XXXXXXXo ",
		"  oXXXX.      o.XX.  .XXo   XXX    o.XXX.   ", NULL};

	return (xpm);
}
