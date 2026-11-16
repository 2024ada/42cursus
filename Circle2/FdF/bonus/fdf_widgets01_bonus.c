/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_widgets01_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ucho <ucho@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 02:08:00 by ucho              #+#    #+#             */
/*   Updated: 2025/08/19 14:14:34 by ucho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

const char	**widget04(void)
{
	static const char	*xpm[] = {"33 31 3 1 ", "  c #292D39", ". c #484D5E",
		"X c #626E81", "         ..XXX..                 ", "      .XXX.. ...XX"
		".              ", "     XX.         .XX.            ", "   .X.        "
		"     .X.           ", "  .X.               .X.          ", "  X.      "
		"           .X          ", " .X                   X.         ", " X.   "
		"                .X         ", " X.                   .X         ", ".X"
		"                     X.        ", ".X                               ",
		" X.                              ", " X.                  ..         "
		" ", " .X               .XXXXXXX.      ", "  XX            .X.      .XX"
		".    ", "  .X.          XX          .X.   ", "   .X         XX        "
		"     X.  ", "   X.        .X              .X  ", "  .X  .XXXX  X.     "
		"          X. ", "  X..XX.  . .X                .X ", " .XX.       .X  "
		"              .X ", "  .         .X                .X ", "            "
		".X                .X ", "             X.               X. ", "        "
		"     .X              .X  ", "              X.            .X.  ", "    "
		"          .X.           XX   ", "                XX.      .  .X.  ",
		"                 .XXX..XXXXX..X  ", "                    ....   .XXX."
		" ", "                              .. ", NULL};

	return (xpm);
}

const char	**widget05(void)
{
	static const char	*xpm[] = {"33 31 3 1 ", "  c #292D39", ". c #484D5E",
		"X c #626E81", "                                 ", "                  "
		"               ", "                                 ", "              "
		".XXXX.             ", "             XX.  .XX            ", "          "
		"  XX      XX           ", "           .X        X.          ", "      "
		"     ..        X.          ", "  XXXXXXXXXXXXXXXXXXXXXXXXXXXXX  ", " ."
		"X...........................X  ", " .X                          .X  ",
		" .X                          .X  ", " .X                          .X "
		" ", " .X           ......         .X  ", " .X           .X..XX        "
		" .X  ", " .X...........X.  .X.........XX  ", " .X...........X.  .X...."
		".....XX  ", " .X           ..  .X         .X  ", " .X           .X..XX"
		"         .X  ", " .X           ......         .X  ", " .X             "
		"             .X  ", " .X                          .X  ", " .X         "
		"                 .X  ", " .X                          .X  ", " .X     "
		"                     .X  ", " .X                          .X  ", " .X."
		"                         .X  ", "  XXXXXXXXXXXXXXXXXXXXXXXXXXXXX  ",
		"                                 ", "                                "
		" ", "                                 ", NULL};

	return (xpm);
}

const char	**widget06(void)
{
	static const char	*xpm[] = {"33 31 3 1 ", "  c #292D39", ". c #484D5E",
		"X c #626E81", "            .XXXXXXX.            ", "         .XX..    "
		" ..XX.         ", "        XX.           .XX        ", "      .X.     "
		"          .X.      ", "     .X.                 .X.     ", "    .X    "
		"                .X.    ", "   .X.                     .X.   ", "   X. "
		"                 ..   .X   ", "  .X                .XXX.    X.  ", "  "
		"X.              .XX..X     .X  ", " .X             .XX.  .X      X. ",
		" ..          .XXX     X.      X. ", " X.         .XX      .X       .X"
		" ", " X.         XXX.     X.       .X ", ".X         .X..X.   .X      "
		"  .X ", ".X         .X  .X.  X.        .X ", ".X        .X.   .X..X   "
		"      .X ", " X.       .X     .XXX         .X ", " X.       X.      XX"
		".         .X ", " ..      .X    .XXX           X. ", " .X      X.  .XX"
		".             X. ", "  X.    .X..XX.              .X  ", "  .X    .XXX"
		"                 X.  ", "   X.   ..                  .X   ", "   .X.  "
		"                   .X.   ", "    .X                    .X.    ", "    "
		" .X.                 .X.     ", "      .X.               .X.      ",
		"        XX.           .XX        ", "         .XX..     ..XX.        "
		" ", "            .XXXXXXX.            ", NULL};

	return (xpm);
}

const char	**widget07(void)
{
	static const char	*xpm[] = {"33 31 3 1 ", "  c #292D39", ". c #484D5E",
		"X c #626E81", "                                 ", "    .             "
		"               ", "  .XX.                           ", " XX..X        "
		"            .XXXXX ", " X.  X.                   X.     ", " .X  .X   "
		"         .X    .X      ", "  X.  X.    .XXXXXXXXX   .X      ", "  .X  "
		".X    X.   .X. XX  X.      ", "  .X.  X.   X.  .X.   X. X.      ", "  "
		" X.  .X   X. .X.    .X.X       ", " ..XX..XX...XXXXX......XXX       ",
		" X......................X.       ", " X.                     X.      "
		" ", " .X                    .X        ", "  X.                   .X   "
		"     ", "  X.                   ..        ", "  .X                   X"
		".        ", "   X.                 .X.        ", "   X.               "
		"  .X         ", "   .X                 ..         ", "   .X           "
		"      X.         ", "    X.                X.         ", "    .X      "
		"         .X          ", "    .XXXXXXXXXXXXXXXXX.          ", "        "
		"             X.          ", "     .XXXXXXXXXXXXXXXXX          ", "    "
		".X  X.        .X  X.         ", "    .X  .X        .X  .X         ",
		"    .X. X.        .X. X.         ", "     .XX.          .XX.         "
		" ", "                                 ", NULL};

	return (xpm);
}

const char	**widget08(void)
{
	static const char	*xpm[] = {"19 19 5 1 ", "  c #FEFEFE", ". c #BBD2D6",
		"X c #71594E", "o c #3D5E9A", "O c #E1F6ED",
		"     .XXo.O        ",
		"   .XXXXXXXoO      ",
		"  XXo.   OXXoO     ",
		" .XoO      XXo     ",
		"OXoO        XX.    ",
		".X.         OXo    ",
		"Xo.          XoO   ",
		"XoO          XoO   ",
		"Xo.          XoO   ",
		".X.         OXo    ",
		"OXoO        XX.    ",
		" .Xo       .Xo     ",
		"  XXo.   OXXXoO    ",
		"   XXXXXXXXoXXoO   ",
		"    OXXXXo.  XXoO  ",
		"              XXoO ",
		"               XXoO",
		"                XoO",
		"                   ", NULL};

	return (xpm);
}
