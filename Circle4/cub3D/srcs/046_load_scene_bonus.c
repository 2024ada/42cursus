/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   050_load_scene_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ucho <ucho@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/09 04:50:11 by ucho              #+#    #+#             */
/*   Updated: 2026/07/09 04:50:11 by ucho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D_bonus.h>

#ifdef BONUS

int	load_intro(t_app *app)
{
	if (load_xpm_image(app, IMAGE"title.xpm", &app->assets.intro_title))
		return (put_err("TEXTURE", "Failed to load: "IMAGE"title.xpm"));
	if (load_xpm_image(app, IMAGE"play_on.xpm", &app->assets.button[0][ON]))
		return (put_err("TEXTURE", "Failed to load: "IMAGE"play_on.xpm"));
	if (load_xpm_image(app, IMAGE"play_off.xpm", &app->assets.button[0][OFF]))
		return (put_err("TEXTURE", "Failed to load: "IMAGE"play_off.xpm"));
	if (load_xpm_image(app, IMAGE"rules_on.xpm",
			&app->assets.button[1][ON]))
		return (put_err("TEXTURE", "Failed to load: "IMAGE"rules_on.xpm"));
	if (load_xpm_image(app, IMAGE"rules_off.xpm",
			&app->assets.button[1][OFF]))
		return (put_err("TEXTURE", "Failed to load: "IMAGE"rules_off.xpm"));
	if (load_xpm_image(app, IMAGE"rules.xpm", &app->assets.intro_rules))
		return (put_err("TEXTURE", "Failed to load: "IMAGE"rules.xpm"));
	if (load_xpm_image(app, IMAGE"prol_00.xpm", &app->assets.prologue[0]))
		return (put_err("TEXTURE", "Failed to load: "IMAGE"prol_00.xpm"));
	if (load_xpm_image(app, IMAGE"prol_01.xpm", &app->assets.prologue[1]))
		return (put_err("TEXTURE", "Failed to load: "IMAGE"prol_01.xpm"));
	if (load_xpm_image(app, IMAGE"prol_02.xpm", &app->assets.prologue[2]))
		return (put_err("TEXTURE", "Failed to load: "IMAGE"prol_02.xpm"));
	if (load_xpm_image(app, IMAGE"prol_03.xpm", &app->assets.prologue[3]))
		return (put_err("TEXTURE", "Failed to load: "IMAGE"prol_03.xpm"));
	if (load_xpm_image(app, IMAGE"prol_04.xpm", &app->assets.prologue[4]))
		return (put_err("TEXTURE", "Failed to load: "IMAGE"prol_04.xpm"));
	return (0);
}

int	load_outro(t_app *app)
{
	if (load_xpm_image(app, IMAGE"fail.xpm", &app->assets.outro_fail))
		return (put_err("TEXTURE", "Failed to load: "IMAGE"fail.xpm"));
	if (load_xpm_image(app, IMAGE"clear.xpm", &app->assets.outro_clear))
		return (put_err("TEXTURE", "Failed to load: "IMAGE"clear.xpm"));
	if (load_xpm_image(app, IMAGE"score.xpm", &app->assets.outro_score))
		return (put_err("TEXTURE", "Failed to load: "IMAGE"score.xpm"));
	if (load_xpm_image(app, IMAGE"exit_on.xpm",
			&app->assets.button[3][ON]))
		return (put_err("TEXTURE", "Failed to load: "IMAGE"exit_on.xpm"));
	if (load_xpm_image(app, IMAGE"exit_off.xpm",
			&app->assets.button[3][OFF]))
		return (put_err("TEXTURE", "Failed to load: "IMAGE"exit_off.xpm"));
	if (load_xpm_image(app, IMAGE"replay_on.xpm",
			&app->assets.button[2][ON]))
		return (put_err("TEXTURE", "Failed to load: "IMAGE"replay_on.xpm"));
	if (load_xpm_image(app, IMAGE"replay_off.xpm",
			&app->assets.button[2][OFF]))
		return (put_err("TEXTURE", "Failed to load: "IMAGE"replay_off.xpm"));
	return (0);
}

int	load_minimap(t_app *app)
{
	if (load_xpm_image(app, IMAGE"mini_hero.xpm", &app->assets.mini_hero))
		return (put_err("TEXTURE", "Failed to load: "IMAGE"mini_hero.xpm"));
	if (load_xpm_image(app, IMAGE"mini_box.xpm", &app->assets.mini_box))
		return (put_err("TEXTURE", "Failed to load: "IMAGE"mini_box.xpm"));
	return (0);
}

#endif
