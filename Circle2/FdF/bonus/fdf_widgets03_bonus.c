/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_widgets03_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ucho <ucho@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 02:08:00 by ucho              #+#    #+#             */
/*   Updated: 2025/08/19 14:14:38 by ucho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

const char	**profile_1(void)
{
	static const char	*profile_1[] = {
		" .&<<4yqryr5w5555ddssruu>", " X&<<4yqrr1tttaaddt1ssru5",
		"O&&<44yq1rrttddddttt1ru15", "p&<44yyq11155adddt000t015",
		".<444yyq1111iw0dtt0000ttu", "8<4ssyyr1tui,6ff0000%%0ug",
		"X4yyyyr11t1hw6<h4500%%ths", "<4yyyqr115<:aw>ihh20%j1i<",
		"4yyyyqr11y8haw,ih>da0j5,,", "4yyyyyqrq.8h,wihh,5w5da>,",
		"4yyyyyqrX9*i>w:hhi,w6dgfd", "<yyyqqqq.9*<h::hhi>w>dkkg",
		"esyyqrqy+O;eee*hhiwadlzkz", "84yqqrry+Op8e**e:>5d0gzgg",
		".syqqrry+O9;88*ei5dgzzggg", "Oyysssy4+O9;88*h>dzzzggjj",
		" <qys44<OO9;8*hi>dgzzggjj", " 811sX8. O9.8*h:>6wfzgjjj",
		" O48p9+O O9;*=hh:iiwgzgjj", "  p99+O O+p;*::h:::,fzggg",
		"   +9O  O9p;*h:::hh>dlzgg", "   O9   O9p;8=::::i>>dzzg",
		"    +   O9p;8=:i,6i:idzzg", "       O+pp;88*ehiii>dgjl",
		"       O99p;88***ehi>dgll", "       O9p;888*88***ei0l0",
		"       Op;88***8888**hiff", "        9;88*ehe888*hhif0",
		"         .<<sq1urqsiqrttu", "          p4##qqqqyyyqroo",
		"           OX4ss4sssyqqrr", "             +X4<<4444#qq",
		"               O;<444##qq", "                  +.8X&$q", NULL};

	return (profile_1);
}

const char	**widget14(void)
{
	static const char	*xpm[100] = {"25 50 48 1 ", "  c #FEFEFD",
		". c #D5D0CD", "X c #B4AEA9", "o c #747067", "O c #F1F0EB",
		"+ c #E7E9E7", "@ c #DBE4E3", "# c #8E8579", "$ c #909188",
		"% c #594F4A", "& c #A6A09B", "* c #C6AB98", "= c #C39D84",
		"- c #7A8679", "; c #D6C7B9", ": c #B28A73", "> c #997565",
		", c #A57965", "< c #A7928F", "1 c #876A65", "2 c #946E63",
		"3 c #B07D63", "4 c #9B8883", "5 c #896559", "6 c #99725E",
		"7 c #A2735E", "8 c #CBB7A9", "9 c #E9E3DA", "0 c #694F4A",
		"q c #8C7772", "w c #946959", "e c #B9A595", "r c #88726A",
		"t c #775A55", "y c #947976", "u c #786459", "i c #A78775",
		"p c #E4D9CE", "a c #855B4F", "s c #96837A", "d c #7A5649",
		"f c #65463A", "g c #54342C", "h c #B89885", "j c #603D37",
		"k c #38211D", "l c #5F4639", "z c #47261D",
		"                   .XXXoo", "                O+@#$%%o&",
		"             OO+++@$&$$##", "           O*=.@++@$ooX-$",
		"          ;:::*.@++$%oX-o", "         X>,,::=+++&o-$o%",
		"        <112,,3:*+O$$oo%%", "      O4111567,3:89XX4%%0",
		"      <q11155w,,3:=e<r%0t", "     8yqqut22>,773::iqutu",
		"    p4yy11112>,,,,::<rouu", "    &44yr11155www7,e<ruou",
		"   8<4yyr115>>2wwwie4rtru", "  O&&<yyr1122w5aa5iesou11",
		"  .&&4yyqrr2www5aa><#uurr", " OX&&4yyqqr2,:::3>>4q1tr>",};

	ft_memcpy(xpm + 65, profile_1(), 35 * sizeof(char *));
	xpm[99] = NULL;
	return (xpm);
}

const char	**profile_2(void)
{
	static const char	*profile_2[] = {
		"69666#,,;4=>457885553@   ", "6066606,,>442455888533O  ",
		"00$;#660,,,>>223555333@  ", "00$2---*;;,,,q1>3333333O ",
		"@@0;2=w5ee2,1rtrq333333. ", "0@@yy0;-w5w,,u,iiq38333> ",
		"00y@pp0,>ww>,aqqs1133333&", "00ypppt,>444,>a>u3>q3335X",
		",,@ddppy,>>>>,>q13uq388f@", "2@::dppygqq;>,1q13u>13556",
		"@::dppyyrg,,,,qgu3>>11>1g", ":::dptyyrgg,,,q1ua>>>1qqg",
		"d:dptyyyrigq>,1uu>>>>1qqq", "pdptyyyyyigq1,>ua11>11qqq",
		",yy0ryyyyigqq,>u>qq111qq,", ",00ggrrrrigqq,au>q,q11q16",
		">g,g00gggg,1>1uu>>>>>>>>@", "753,gggg,,1a>>333>>>>>>2:",
		"ww4,,,,,,>3542334>>>2222<", "4ww00g,q47fe55554422222=&",
		"42400gq4fhjjffhkhf74444* ", "42w2;2efjlllfhzlllljfee. ",
		"44wwweefklllhjlllllljf7& ", "44ww7eeeklllzhzlllllzh9  ",
		"4w57w4wexxzzzkjlllllzkO  ", "2222--4ezzzzzzkzllllxc   ",
		"2--*$$-7zzzzzzxxlzxzk&   ", "-**$$$-whzzzzzxxzlzz.    ",
		"-;$6#$-=ezxzzxxxzll      ", ";$#6$*-=wkzzxxzzzlw&     ",
		";$##$*-2wejxxxzzze&      ", "$$#6$*--=whzxxxz%&       ",
		"666#$*--227zxxx9         ", "96#$**%-2-5zxkX          ",
		"996$$*--->3j &           ", "996$$*-2;>@O             ",
		"@96#$*-$.&               ", "@d...XO                  ", NULL};

	return (profile_2);
}

const char	**widget15(void)
{
	static const char	*xpm[102] = {"25 50 50 1 ", "  c #615D60",
		". c #A49D93", "X c #B4B1AA", "o c #C6C3BF", "O c #DEDAD7",
		"  c #FEFEFE", "@ c #8E7568", "# c #6F6356", "$ c #6A5B53",
		"% c #5D534A", "& c #EBE8E7", "* c #665549", "= c #534437",
		"- c #5A4B42", "; c #6A5348", ": c #AE958B", "> c #684737",
		", c #785746", "< c #C4B8B0", "1 c #6E4936", "2 c #574339",
		"3 c #573827", "4 c #563C33", "5 c #4A3326", "6 c #766458",
		"7 c #462E26", "8 c #452D1D", "9 c #7A6C65", "0 c #866556",
		"q c #734B39", "w c #4A3733", "e c #392925", "r c #8E624D",
		"t c #A06D59", "y c #956656", "u c #623B2A", "i c #8D5D49",
		"p c #A57969", "a c #643E30", "s c #81533D", "d c #AB8476",
		"f c #34221C", "g c #855B4B", "h c #271915", "j c #1A100E",
		"k c #191314", "l c #0D0909", "z c #120C0C", "x c #120D10",
		"c c #5B585A", " .XXXoO                  ", ".X.@#$%#.&               ",
		".@%##$%%%*.O             ", "#%=$*%%%--*;:&           ",
		"-%=%--%%*-*>>,<          ", "--%====-=--;111:         ",
		"%*%%-==22=22222>@        ", "$*%$%-==2=22=3333,&      ",
		"$$**$--=2=444355556      ", "$6**$$-==-235755588@     ",
		"66#*##*-222355557785<    ", "6#66$###=2>4577555783&   ",};

	ft_memcpy(xpm + 63, profile_2(), 39 * sizeof(char *));
	xpm[101] = NULL;
	return (xpm);
}
