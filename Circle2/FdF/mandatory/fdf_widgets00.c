/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   widgets00.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ucho <ucho@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 02:08:00 by ucho              #+#    #+#             */
/*   Updated: 2025/06/21 19:27:32 by ucho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

const char	**forty(void)
{
	static const char	*xpm[] = {
		"   oXXXXXXXXXX                       oXXXXXXXXXX.     ",
		"  oXXXXXXXXXX                       oXXXXXXXXXX.      ",
		" oXXXXXXXXXX                       oXXXXXXXXXX.       ",
		"oXXXXXXXXXX                       oXXXXXXXXXX         ",
		"XXXXXXXXXX....................    XXXXXXXXXX         o",
		"XXXXXXXXXXXXXXXXXXXXXXXXXXXXXX    XXXXXXXXXX        oX",
		"XXXXXXXXXXXXXXXXXXXXXXXXXXXXXX    XXXXXXXXXX       .XX",
		"XXXXXXXXXXXXXXXXXXXXXXXXXXXXXX    XXXXXXXXXX      .XXX",
		"XXXXXXXXXXXXXXXXXXXXXXXXXXXXXX    XXXXXXXXXX     .XXXX",
		"XXXXXXXXXXXXXXXXXXXXXXXXXXXXXX    XXXXXXXXXX    .XXXXX",
		"XXXXXXXXXXXXXXXXXXXXXXXXXXXXXX    XXXXXXXXXX   .XXXXXX",
		"XXXXXXXXXXXXXXXXXXXXXXXXXXXXXX    XXXXXXXXXX  .XXXXXXX",
		"....................XXXXXXXXXX    XXXXXXXXXX .XXXXXXXX",
		"                   oXXXXXXXXXX    XXXXXXXXXX.XXXXXXXXX",
		"                   oXXXXXXXXXX    oooooooooooooooooooo",
		"                   oXXXXXXXXXX                        ",
		"                   oXXXXXXXXXX                        ",
		"                   oXXXXXXXXXX                        ",
		"                   oXXXXXXXXXX                        ",
		"                   oXXXXXXXXXX                        ",
		"                   oXXXXXXXXXX                        ",
		"                   oXXXXXXXXXX                        ", NULL};

	return (xpm);
}

const char	**widget00(void)
{
	static const char	*xpm[43] = {"54 37 4 1 ", "  c #292D39", ". c #626E81",
		"X c #F4F5F5", "o c #484D5E",
		"                   .XXXXXXXXX.    XXXXXXXXX.XXXXXXXXXX",
		"                  XXXXXXXXXX.     XXXXXXXX. XXXXXXXXXX",
		"                 XXXXXXXXXX.      XXXXXXX.  XXXXXXXXXX",
		"                XXXXXXXXXX.       XXXXXX.   XXXXXXXXXX",
		"               XXXXXXXXXX.        XXXXX.    XXXXXXXXXX",
		"              XXXXXXXXXX.         XXXX.     XXXXXXXXXX",
		"             XXXXXXXXXX.          XXX.      XXXXXXXXXX",
		"            XXXXXXXXXX.           XX.       XXXXXXXXXX",
		"           XXXXXXXXXX.            X.        XXXXXXXXXX",
		"          XXXXXXXXXX.             .         XXXXXXXXXX",
		"         XXXXXXXXXX.                       XXXXXXXXXX.",
		"       oXXXXXXXXXX.                       XXXXXXXXXX. ",
		"      oXXXXXXXXXX.                       XXXXXXXXXX.  ",
		"     oXXXXXXXXXX.                       XXXXXXXXXX.   ",
		"    oXXXXXXXXXX.                       XXXXXXXXXX.    ",};

	ft_memcpy(xpm + 20, forty(), 23 * sizeof(char *));
	xpm[42] = NULL;
	return (xpm);
}

const char	**widget01(void)
{
	static const char	*xpm[] = {"33 31 3 1 ", "  c #292D39", ". c #484D5E",
		"X c #626E81", "             ..XXXXX.            ", "            .X.   "
		"  .X.          ", "          .XX.        X.         ", "          X.  "
		"        ..         ", "         .X           ..         ", "         ."
		"X           X.         ", "          X.         .X.         ", "      "
		"    X.         .X          ", "          .X         X.          ", "  "
		"        X.         .X          ", "         .X          .X          ",
		"          X.         .X          ", "          .X         X.         "
		" ", "          .X         X           ", "           X.       .X      "
		"     ", "           .X      .X.           ", "            X.     .X   "
		"         ", "            X.     .X            ", "            X.     ."
		"X            ", "            X.     .X            ", "          .XX.  "
		"   .XX.          ", "       .XX.          ..XX.       ", "     .XX.   "
		"            .XX.     ", "   .XX                    .XX.   ", "  .X.   "
		"                    .X.  ", "  X.                         .X  ", " .X "
		"                          X. ", " X.                           X. ",
		" X.                           .X ", " X.                           .X"
		" ", ".XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX ", NULL};

	return (xpm);
}

const char	**widget02(void)
{
	static const char	*xpm[] = {"33 31 4 1 ", "  c #292D39", ". c #626E81",
		"X c #F4F5F5", "o c #484D5E", "                           .XXX. ", "   "
		"                       .XX.XXo", "                          .Xo .X.",
		"                          .XXoXXo", "  ...                     .XXXX."
		" ", " XXXXXo                  .XXo.   ", ".XX .X.                 .XX "
		"     ", ".X. .X.          ...   .XX       ", "oXX.XXXX.o     XXXXXXXXX"
		"X        ", " .XXX.oXXXX. oXXXo  .XXX         ", "         .XXXXX.    "
		" .XX         ", "           .XXX       .X.        ", "            .X. "
		"      .X.        ", "            .X.       oX.        ", "            "
		".X.       .X.        ", "            oXX       XXXo       ", "        "
		"     .X.     .XXXXX.XXX. ", "             .XXX. oXXXoo.XXX.XXo", "    "
		"        .XX.XXXXX.    .Xo .X.", "           .XX    XXo     .XXoXXo",
		"          .XX     XXo      XXXX. ", "         .XX      XXo       o.o "
		" ", "        .XX       XXo            ", "       .XX        XXo       "
		"     ", "      .XX         XXo            ", "   .o.XX          XXo   "
		"         ", " .XXXXX         oXXXX.           ", ".XXo.X.         XX.o"
		"XX           ", ".X. .X.         XX  XXo          ", "oXX.XX.         "
		".X..XX           ", " .XXX.          oXXXXo           ", NULL};

	return (xpm);
}

const char	**widget03(void)
{
	static const char	*xpm[] = {"33 31 3 1 ", "  c #292D39", ". c #626E81",
		"X c #484D5E", "                                 ", "                  "
		"               ", "                                 ", "              "
		"                   ", " ............................... ", "X.X       "
		".X         X.       X. ", "X.        .X         X.       X. ", "X.    "
		"    .X         X.       X. ", "X............................... ", "X."
		"XXXXXXXXXXXXXXXXXXXXXXXXXXXXX. ", "X.                            X. ",
		"X.                            X. ", "X.          XX                X."
		" ", "X.          ...X              X. ", "X.          .XX..X          "
		"  X. ", "X.          .X   X..X         X. ", "X.          .X    X..   "
		"      X. ", "X.          .X X...           X. ", "X.          ....X   "
		"          X. ", "X.          ..X               X. ", "X.              "
		"              X. ", "X.                            X. ", "X.X         "
		"                  X. ", "X............................... ", "X.      "
		"  .X         X.       X. ", "X.        .X         X.       X. ", "X.X "
		"      .X         X.       X. ", " ............................... ",
		"                                 ", "                                "
		" ", "                                 ", NULL};

	return (xpm);
}
