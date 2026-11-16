/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   widgets05.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ucho <ucho@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 02:08:00 by ucho              #+#    #+#             */
/*   Updated: 2025/06/21 19:29:11 by ucho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

const char	**widget21(void)
{
	static const char	*xpm[] = {"21 19 5 1 ", "  c #1E212A",
		". c #29375A", "X c #5C6268", "o c #2E242B", "O c #616D80",
		"        .XXXo        ",
		"      .OXX.XXXo      ",
		"   .XOXo     .XXXo   ",
		" .OOXo         .OOXo ",
		".OOXo           .OOXo",
		".XoXOX.       XXX..Xo",
		".Xo  .XXXo .XXXo  .Xo",
		".Xo    .XOOX.o    .Xo",
		".Xo      .Xo      .Xo",
		".Xo      .Xo      .Xo",
		".Xo      .Xo      .Xo",
		".Xo      .Xo      .Xo",
		".Xo      .Xo      .Xo",
		".Xo      .Xo      .Xo",
		".Xo      .Xo      XXo",
		" .XXXo   .Xo   .XOXo ",
		"   .XOX. .Xo .OXXo   ",
		"      .XXXXXOXo      ",
		"        .XXXo        ", NULL};

	return (xpm);
}

const char	**widget22(void)
{
	static const char	*xpm[] = {"21 19 5 1 ", "  c #1E212A", ". c #27232C",
		"X c #5E6F86", "o c #DFE1D5", "O c #523A47",
		"       .XoooX        ",
		"     XooooXoooXO     ",
		"  .XoooXO   XooooX   ",
		"OooooX.       .XoooX.",
		"XoooX.         .XoooO",
		"XoXooooO     XooooXoO",
		"XoO .XoooXOXoooX. XoO",
		"XoO    XoooooO    XoO",
		"XoO      XoO      XoO",
		"XoO      XoO      XoO",
		"XoO      XoO      XoO",
		"XoO      XoO      XoO",
		"XoO      XoO      XoO",
		"XoO      XoO      XoO",
		"XooO     XoO     XooO",
		".ooooX   XoO  .XoooX ",
		"  .XoooXOXoOXooooX   ",
		"     XooooooooXO     ",
		"       .XoooX        ", NULL};

	return (xpm);
}

const char	**widget23(void)
{
	static const char	*xpm[] = {"21 19 4 1 ", "  c #1E212A",
		". c #445265", "X c #656E80", "o c #2C232E",
		" .XXXXXXXXXXXXXXXXXo ",
		"oXoooo.Xoooo.Xoooo.Xo",
		"oXo   oXo   .Xo   .Xo",
		"oXo   oXo   .Xo   .Xo",
		"oXo   oXo   .Xo   .Xo",
		"oXo   oXo   .Xo   .Xo",
		"oXXXXXXXXXXXXXXXXXXXo",
		"oXo   oXo   .Xo   .Xo",
		"oXo   oXo   .Xo   .Xo",
		"oXo   oXo   .Xo   .Xo",
		"oXo   oXo   .Xo   .Xo",
		"oXoooo.Xoooo.Xoooo.Xo",
		"oXXXXXXXXXXXXXXXXXXXo",
		"oXo   .Xo   .Xo   .Xo",
		"oXo   oXo   .Xo   .Xo",
		"oXo   oXo   .Xo   .Xo",
		"oXo   oXo   .Xo   .Xo",
		"oXoooo.Xoooo.Xoooo.Xo",
		" .XXXXXXXXXXXXXXXXXo ", NULL};

	return (xpm);
}

const char	**widget24(void)
{
	static const char	*xpm[] = {"21 19 5 1 ", "  c #22232C", ". c #E1E5D8",
		"X c #5C6E85", "o c #1E212A", "O c #5F434E",
		" ..................Xo",
		"X.XXXXX.XXXXX.XXXX..O",
		"X.OoooX.OoooX.OoooX.O",
		"X.OoooX.OoooX.OoooX.O",
		"X.OoooX.OoooX.OoooX.O",
		"X.OoooX.OoooX.OoooX.O",
		"X...................O",
		"X.OoooX.OoooX.OoooX.O",
		"X.OoooX.OoooX.OoooX.O",
		"X.OoooX.OoooX.OoooX.O",
		"X.OoooX.OoooX.OoooX.O",
		"X.XXXXX.XXXXX.XXXXX.O",
		"X...................O",
		"X.OoooX.OoooX.OoooX.O",
		"X.OoooX.OoooX.OoooX.O",
		"X.OoooX.OoooX.OoooX.O",
		"X.OoooX.OoooX.OoooX.O",
		"X.XXXXX.XXXXX.XXXX..O",
		" ..................Xo", NULL};

	return (xpm);
}

const char	**widget25(void)
{
	static const char	*xpm[] = {"21 19 4 1 ", "  c #1E212A", ". c #434A5C",
		"X c #616C80", "o c #2E262D",
		"     .XXXXX.         ",
		"   oXX.ooo.XXo       ",
		"  .X.     o .Xo      ",
		"  X.    oo   .Xo     ",
		" .Xo    Xo    X.     ",
		" Xo     Xo    .Xo    ",
		"oXo     Xo     Xo    ",
		".Xo .XXXXXXX.  Xo    ",
		".Xo ooooXoooo oXo    ",
		" Xo     Xo    .Xo    ",
		" ..     Xo    ..o    ",
		" .Xo    .o   .Xo     ",
		"  .Xo       oXXo     ",
		"   .X.o    .XXXXo    ",
		"    .XXXXXXXo.XXXo   ",
		"      o...o   .XXXo  ",
		"               .XXXo ",
		"                .XX. ",
		"                 .X. ", NULL};

	return (xpm);
}
