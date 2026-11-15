/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ucho <ucho@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/09 05:15:36 by ucho              #+#    #+#             */
/*   Updated: 2026/07/09 05:15:36 by ucho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_BONUS_H
# define CUB3D_BONUS_H

# include "cub3D.h"

/* Global Settings */
# define LEFT 0
# define RIGHT 1
# define OFF 0
# define ON 1
# define WEIGHT 100000
# define SCORE 100

/* Math Constants */
# define EPSILON 1e-6
# define PI 3.1415926535

/* Asset Settings */
# define IMAGE "./assets/images/"
# define FONT "./assets/fonts/"
# define ITEM_GOAL_COUNT 11

/* Scene Settings */
# define GAME 0
# define INTRO_TITLE 1
# define INTRO_RULES 2
# define FADEOUT_TITLE 3
# define FADEIN_PROL 4
# define INTRO_PROL 5
# define FADEOUT_PROL 6
# define FADEIN_GAME 7
# define FADEOUT_GOAL 8
# define DISSOLVE_FAIL 9
# define DISSOLVE_CLEAR 10
# define OUTRO_FAIL 11
# define OUTRO_CLEAR 12
# define DISSOLVE 2.0
# define GAME_HALF 6
# define CEIL_DISSOLVE_TIME 0.3

/* UI Settings */
# define BUTTON_X 119
# define BUTTON_LEFT_Y 660
# define BUTTON_RIGHT_Y 828
# define BUTTON_W 377
# define BUTTON_H 134
# define CLOSE_X 930
# define CLOSE_Y 967
# define CLOSE_W 57
# define CLOSE_H 63
# define NEXT_X 1485
# define NEXT_Y 973
# define NEXT_W 200
# define NEXT_H 34
# define FINAL_SCORE_X 1604
# define FINAL_SCORE_Y 480
# define FINAL_SCORE_SCALE 2.0
# define FINAL_SCORE_COLOR 0x00BE8C26

/* Hero Settings */
# define HERO_HP 100
# define HERO_AP 40
# define HERO_SIGHT 1.6
# define HERO_ANGLE 0.82
# define HERO_PAIN_TIME 0.5
# define HERO_ATTACK_STEP 2
# define HERO_GEAR 6

/* Mob Settings */
# define MOB_MAX 64
# define MOB_HP 100
# define MOB_AP 8
# define MOB_MARGIN 0.1
# define MOB_SIGHT 4.0
# define MOB_ANGLE 0.35
# define MOB_SPEED 0.01
# define MOB_SLIDE 2.0
# define MOB_CHASE_TIME 1.2
# define MOB_PAIN_TIME 0.8
# define MOB_COOL_TIME 1.0
# define MOB_ATTACK_RANGE 1.3
# define MOB_ATTACK_TIER 5
# define MOB_ATTACK_STEP 2
# define MOB_THREAT_BIAS 1.35
# define MOB_PAIN_TIER 5
# define MOB_MAX 64

/* Item Settings */
# define ITEM_GET_RANGE 0.45
# define ITEM_HP 20
# define ITEM_HEAL_TIER 5
# define ITEM_HEAL_STEP 5
# define ITEM_GEAR_CHARGE 3

/* Camera Settings */
# define MOUSE_SENS 0.001
# define H_FOV_MIN 0.35
# define H_FOV_MAX 1.40
# define V_FOV_MIN 1.00
# define V_FOV_MAX 2.80

/* Raycasting */
# define RAY_STEP 0.05

/* Rendering Settings */
# define PROP_SCALE 0.5
# define DOOR_PASS_RATIO 0.25
# define ITEM_GOAL_SCALE 0.1
# define ITEM_HEAL_SCALE 0.3
# define ITEM_GEAR_SCALE 0.12

/* Font Settings */
# define FONT_SPACING 4
# define FONT_SPACE 14
# define FONT_CENTER 1
# define FONT_RIGHT 2

/* HUD Settings */
# define HUD_GEAR_X 540
# define HUD_GEAR_Y 950
# define HUD_GEAR_W 80
# define HUD_GEAR_H 80
# define HUD_ROUND_X 92
# define HUD_ROUND_Y 942
# define HUD_HP_X 212
# define HUD_HP_Y 942
# define HUD_SCORE_X 305
# define HUD_SCORE_Y 942
# define HUD_ITEM_X 443
# define HUD_ITEM_Y 1007
# define HUD_CHARGE_X 645
# define HUD_CHARGE_Y 950
# define HUD_TEXT_SCALE 0.5
# define HUD_ITEM_SCALE 0.37
# define HUD_CHARGE_SCALE 0.45
# define HUD_TEXT_COLOR 0x00FFFFFF
# define HUD_ITEM_COLOR 0x00010102
# define HUD_CHARGE_COLOR 0x00FDF08F
# define HAND_IDLE 0
# define HAND_SHOT 1
# define FRAME_DELAY 0
# define NONE 0
# define DEATH 1
# define PAIN 2

/* Minimap Settings */
# define MINI_X 1440
# define MINI_Y 800
# define MINI_W 400
# define MINI_H 230
# define MINI_TILE 50
# define MINI_HERO_SCALE 0.4
# define MINI_WALL_COLOR 0x009C6B04
# define MINI_FLOOR_COLOR 0x008D7E5E
# define MINI_DOOR_COLOR 0x0089500D
# define MINI_GOAL_COLOR 0x007C2300
# define MINI_EMPTY_COLOR 0x00011122
# define MINI_HERO_COLOR 0x00E83F4F

/* X11 Key Codes */
# define XKEY_C 0x0063
# define XKEY_X 0x0078
# define XKEY_Z 0x007a

/* X11 Event Codes */
# define XEVENT_BUTTON_PRESS 4
# define XEVENT_BUTTON_RELEASE 5
# define XEVENT_MOTION_NOTIFY 6

/* X11 Event Masks */
# define XMASK_BUTTON_PRESS 4
# define XMASK_BUTTON_RELEASE 8
# define XMASK_POINTER_MOTION 64

/* Mob Sprite Types */
# define MOB_FRONT 0
# define MOB_BACK 1
# define MOB_LEFT 2
# define MOB_RIGHT 3
# define MOB_ATTACK 4
# define MOB_DEATH 5

/* Parse */
const char	*optional_ids(void);
int			count_tile(t_game *game, char tile);
int			is_empty_tile(t_game *game, t_ixy tile);
int			has_prop(t_vec *props, t_ixy tile);
int			has_mob(t_vec *mobs, t_ixy tile);
int			has_item(t_vec *items, t_ixy tile);
double		rate_item_tile(t_game *game, t_vec *items, t_ixy tile);
int			parse_texture_vec(t_tex_seq *seq, char *line, char *id);
int			parse_texture(t_tex *tex, char *line, char *id);
int			parse_door(t_game *game, char *line);
int			parse_mob(t_game *game, char *line);
int			parse_hand(t_game *game, char *line);
int			parse_item(t_game *game, char *line);
int			check_door(t_game *game);
int			check_goal(t_game *game);
int			check_prop(t_game *game);
int			check_item(t_game *game);
int			is_mob_complete(t_game *game, t_idx type);
int			check_mob(t_game *game);
int			set_mob_ap(t_idx type);
void		count_mob(t_game *game, t_num *counts);
int			set_hero_ap(t_idx type);
int			count_gear(t_game *game, t_num *counts);
int			get_hero_ap(t_mob *mob, double dist, double dot);
int			set_item_hp(t_idx type);
int			get_health_budget(t_game *game, t_num *counts);
int			count_heal(t_game *game, t_num *counts);
char		**copy_map(t_game *game);
void		set_zone_map(t_game *game);

/* Init */
void		init_cub(t_game *game);
void		init_runtime(t_app *app, t_game *game);
void		reset_runtime(t_app *app, t_game *game);
void		save_snapshot(t_game *game);
void		load_snapshot(t_app *app, t_game *game);
int			load_intro(t_app *app);
int			load_outro(t_app *app);
int			load_minimap(t_app *app);
int			load_font(t_app *app);
void		load_background(t_app *app, t_game *game);
int			load_hand(t_app *app, t_game *game);
int			load_prop(t_app *app, t_game *game);
int			load_item(t_app *app, t_game *game);
int			load_mob(t_app *app, t_game *game);
int			load_door(t_app *app, t_game *game);
void		get_door_jamb(t_img *tex, t_door_shape *door);
double		get_prop_half(t_img *img);
void		set_wall_deco(t_game *game, t_num num_wall, t_num num_deco);
void		init_item_goal(t_game *game);
void		init_item_heal(t_game *game);
void		set_item_heal(t_game *game, t_ixy *cand, t_num count, t_idx *types);
void		init_item_gear(t_game *game);
void		set_item_gear(t_game *game, t_ixy *cand, t_num count, t_idx *types);
void		init_mob_list(t_game *game);

/* Render */
int			get_tiled_pixel(t_img *img, t_dxy pos, double width, double height);
int			has_transparent_pixel(t_img *tex, t_pos x);
int			is_transparent_pixel(t_img *tex, unsigned char *mask, t_idx i);
void		draw_scaled_img(t_img *dst, t_img *src, t_rect rect);
void		draw_clipped_img(t_img *dst, t_img *src, t_rect rect, t_rect clip);
void		draw_overlay(t_app *app, t_img *tex);
void		draw_ceil(t_img *screen, t_game *game);
void		draw_floor(t_img *screen, t_game *game);
int			blend_color(int from, int to, double alpha);
void		draw_dissolve(t_img *dst, t_img *from, t_img *to, double alpha);
void		draw_number(t_app *app, t_num value, t_text text);
void		draw_doorhead(t_app *app, t_game *game, t_pos x);
void		draw_doorleft(t_app *app, t_game *game, t_pos x);
void		draw_doorright(t_app *app, t_game *game, t_pos x);
int			set_doorhead_sample(t_game *game, t_ray_hit hit, double dist,
				t_sample *pt);
void		draw_doorhead_span(t_app *app, t_game *game, t_pos x,
				t_sample span[2]);
int			set_left_sample(t_game *game, t_ray_hit hit, int frame_y,
				t_sample *pt);
void		draw_left_pixel(t_app *app, t_game *game, t_ixy pos, t_sample pt);
int			set_right_sample(t_game *game, t_ray_hit hit, int frame_y,
				t_sample *pt);
void		draw_right_pixel(t_app *app, t_game *game, t_ixy pos, t_sample pt);
void		draw_sprites(t_app *app, t_game *game);
void		draw_billboard(t_app *app, t_game *game, t_tex *tex,
				double bill[3]);
void		sort_sprites(t_sprite *sprites, t_num count);
void		collect_mob_sprites(t_game *game, t_sprite *sprites, t_num *count);
void		collect_prop_sprites(t_game *game, t_sprite *sprites, t_num *count);
void		collect_item_sprites(t_game *game, t_sprite *sprites, t_num *count);
t_tex		*get_mob_tile(t_game *game, t_mob *mob);
void		draw_hud(t_app *app, t_game *game);
void		draw_minimap(t_app *app, t_game *game);
void		draw_outro(t_app *app, t_game *game);
void		draw_intro(t_app *app, t_game *game);
void		draw_button(t_app *app, t_bool is_ending);

/* Runtime */
int			mouse_press(int button, t_pos x, t_pos y, t_app *app);
void		get_mouse_pos(t_app *app, t_pos x, t_pos y);
int			mouse_release(int button, t_pos x, t_pos y, t_app *app);
int			mouse_move(t_pos x, t_pos y, t_app *app);
int			is_mouse_in_rect(t_app *app, t_rect rect);
void		increase_hfov(t_game *game);
void		decrease_hfov(t_game *game);
void		increase_vfov(t_game *game);
void		decrease_vfov(t_game *game);
int			get_jamb_box(t_game *game, t_ixy tile, t_box box[2]);
int			overlap_prop(t_game *game, t_box actor);
int			is_door_empty(t_game *game, t_pos map_x, t_pos map_y);
void		exec_door(t_game *game);
void		exec_item(t_game *game);
void		exec_mobs(t_game *game);
void		exec_mob_death(t_game *game, t_mob *mob);
void		exec_mob_pain(t_mob *mob);
void		exec_mob_attack(t_game *game, t_mob *mob, double dist);
void		exec_mob_chase(t_game *game, t_mob *mob);
void		exec_mob_patrol(t_game *game, t_mob *mob);
int			is_mob_blocked(t_game *game, double x, double y);
int			spot_hero(t_game *game, t_mob *mob, double *dist);
int			set_mob_dir(t_mob *mob, t_dxy target);
void		move_mob(t_game *game, t_mob *mob, t_dxy target);
void		face_mob_to_hero(t_game *game, t_mob *mob);
void		switch_hand(t_game *game, int keycode);
void		run_hand_fire(t_game *game);
void		set_hand(t_game *game, t_vec *hand);
void		set_effect(t_app *app, t_game *game, t_vec *effect);
void		inherit_stat(t_game *prev, t_game *next);

/* Utility */
int			ft_rand(void);
double		get_now(void);
void		free_tex(void *elem);
void		destroy_texture_vec(t_app *app, t_vec *texs);
void		remove_tex(t_app *app, t_vec *texs, t_idx i);
t_img		*get_vec_img(t_vec *vec, t_idx i);
void		free_door(t_app *app, t_game *game);
void		free_mob(t_app *app, t_game *game);
void		free_texs(t_tex tex[DOOR_COUNT][SLOT_COUNT], t_idx type,
				t_num count);

#endif
