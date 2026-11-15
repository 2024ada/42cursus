/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ucho <ucho@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/08 04:57:08 by ucho              #+#    #+#             */
/*   Updated: 2026/07/09 05:25:40 by ucho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <time.h>
# include <unistd.h>
# include <math.h>

# include <minilibx-linux/mlx.h>
# include <libft.h>
# include "cub3D_getline.h"
# include "cub3D_vector.h"

/* Build Settings */
# ifdef BONUS
#  define GAME_MAX 10
# else
#  define GAME_MAX 1
# endif

/* Global Settings */
# define INT_MAX 2147483647
# define QUEUE_MAX 32
# define TRANSPARENT 0xFF000000

/* Screen Size */
# define WIN_W 1280
# define WIN_H 720
# define REND_W 1920
# define REND_H 1080

/* Asset Settings */
# define SLOT_COUNT 26
# define FONT_COUNT 36
# define TOGGLE_COUNT 2
# define BUTTON_COUNT 4

/* Scene Settings */
# define PROL_COUNT 5

/* Hero Settings */
# define HERO_MARGIN 0.1

/* X11 Key Codes */
# define XKEY_ESC 0xff1b
# define XKEY_LEFT 0xff51
# define XKEY_RIGHT 0xff53
# define XKEY_SPACE 0x0020
# define XKEY_A 0x0061
# define XKEY_D 0x0064
# define XKEY_E 0x0065
# define XKEY_F 0x0066
# define XKEY_Q 0x0071
# define XKEY_R 0x0072
# define XKEY_S 0x0073
# define XKEY_W 0x0077

/* X11 Event Codes */
# define XEVENT_KEY_PRESS 2
# define XEVENT_KEY_RELEASE 3
# define XEVENT_DESTROY_NOTIFY 17

/* X11 Event Masks */
# define XMASK_KEY_PRESS 1
# define XMASK_KEY_RELEASE 2
# define XMASK_STRUCTURE_NOTIFY 131072

/* Mob Sprite Types */
# define MOB_COUNT 6

typedef enum e_key_id
{
	KEY_W,
	KEY_S,
	KEY_A,
	KEY_D,
	KEY_LEFT,
	KEY_RIGHT,
	KEY_Q,
	KEY_E,
	KEY_R,
	KEY_F,
	KEY_SPACE,
	KEY_COUNT
}	t_key_id;

typedef enum e_wall_dir
{
	WALL_NORTH,
	WALL_SOUTH,
	WALL_WEST,
	WALL_EAST,
	WALL_DIR_COUNT
}	t_wall_dir;

typedef enum e_background_kind
{
	FLOOR,
	CEIL,
	BACKGROUND_COUNT
}	t_background_kind;

typedef enum e_door_id
{
	DOOR_FRAME,
	DOOR_PANEL,
	DOOR_HEAD,
	DOOR_LEFT,
	DOOR_RIGHT,
	DOOR_COUNT
}	t_door_id;

typedef enum e_mob_mode
{
	MOB_PAIN,
	MOB_DEAD,
	MOB_PATROL,
	MOB_CHASE,
	MOB_SHOOT
}	t_mob_mode;

typedef int		t_pos;
typedef int		t_dim;
typedef int		t_idx;
typedef int		t_num;
typedef int		t_bool;
typedef char	*t_str;

typedef struct s_ixy
{
	t_pos	x;
	t_pos	y;
}	t_ixy;

typedef struct s_iwh
{
	t_dim	w;
	t_dim	h;
}	t_iwh;

typedef struct s_dxy
{
	double	x;
	double	y;
}	t_dxy;

typedef struct s_rect
{
	t_ixy	pos;
	t_iwh	size;
}	t_rect;

typedef struct s_box
{
	t_dxy	center;
	t_dxy	half;
}	t_box;

typedef struct s_sprite
{
	t_idx	type;
	double	dist;
	t_idx	i;
}	t_sprite;

typedef struct s_text
{
	t_ixy	pos;
	double	scale;
	int		color;
	int		align;
}	t_text;

typedef struct t_point
{
	double	dist;
	t_dxy	local;
	double	z;
	double	screen_y;
}	t_sample;

typedef struct s_column
{
	t_pos	x;
	t_pos	y[3];
	t_pos	clip[2];
	t_dim	height;
	double	pitch;
	double	wall_x;
}	t_column;

typedef struct s_billboard
{
	t_dxy	trans;
	t_ixy	screen;
	t_iwh	size;
	t_ixy	start;
	t_ixy	end;
	t_ixy	real;
	t_iwh	wall;
	double	pitch;
}	t_billboard;

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
	t_iwh	size;
}	t_img;

typedef struct s_tex
{
	t_img	img;
	t_str	path;
}	t_tex;

typedef struct s_tex_seq
{
	t_vec	vec;
}	t_tex_seq;

typedef struct s_ceil_anim
{
	t_img	*curr;
	t_img	*next;
	double	alpha;
}	t_ceil_anim;

typedef struct s_door_shape
{
	t_pos	pivot;
	t_pos	*jamb_left;
	t_pos	*jamb_right;
	double	*jamb_head;
}	t_door_shape;

typedef struct s_ray
{
	double	camera_x;
	t_dxy	dir;
	t_dxy	delta_dist;
	t_dxy	side_dist;
	t_ixy	map;
	t_ixy	step;
	t_idx	side;
}	t_ray;

typedef struct s_face
{
	t_ixy	map;
	t_idx	side;
	double	dist;
}	t_face;

typedef struct s_ray_hit
{
	t_ray	ray;
	t_face	*walls;
	t_face	*doors;
	t_face	*face;
	double	span[2];
}	t_ray_hit;

typedef struct s_dmap
{
	double	progress;
	double	opened_at;
	t_bool	target;
}	t_dmap;

typedef struct s_map
{
	char	**grid;
	int		**zone;
	int		**deco;
	t_dmap	**door;
	t_iwh	size;
	t_num	zone_count;
}	t_map;

typedef struct s_scene
{
	t_map	map;
	t_dxy	pos;
	t_dxy	dir;
	t_dxy	plane;
	t_num	count;
}	t_scene;

typedef struct s_cam
{
	t_dxy	pos;
	t_dxy	dir;
	t_dxy	plane;
	double	v_fov;
	double	default_v_fov;
	double	default_plane_len;
	double	eye_level;
}	t_cam;

typedef struct s_prop
{
	t_dxy	pos;
	t_idx	type;
}	t_prop;

typedef struct s_item
{
	t_dxy	pos;
	t_idx	type;
	t_idx	kind;
	t_bool	is_active;
}	t_item;

typedef struct s_mob
{
	t_dxy		pos;
	t_idx		type;
	t_dxy		dir;
	t_num		hp;
	t_num		ap;
	double		damage_resist;
	double		last_update_time;
	double		last_attack_time;
	t_mob_mode	pain_return_state;
	t_bool		is_alive;
	struct s_anim
	{
		double		frame;
		double		elapsed;
		t_mob_mode	mode;
	} anim;
}	t_mob;
typedef struct s_entity
{
	t_vec	props;
	t_vec	items;
	t_vec	mobs;
}	t_entity;

typedef struct s_history
{
	t_num	num_goal;
	t_num	gear_charge[SLOT_COUNT];
	t_num	hero_hp;
	t_num	hero_score;
	double	now;
	t_idx	ceil_done;
	double	ceil_started_at;
	t_bool	round_loaded;
}	t_history;

typedef struct s_hud
{
	struct s_hand
	{
		t_idx	mode;
		t_idx	frame;
		t_num	tick;
		t_idx	base_gear;
		t_bool	is_shot;
		t_idx	queue[QUEUE_MAX];
		t_idx	queue_head;
		t_idx	queue_tail;
	}	hand;
	struct s_effect
	{
		t_idx	mode;
		t_idx	frame;
		t_num	tick;
		t_bool	is_done;
		double	hurt_until;
	}	effect;
}	t_hud;

typedef struct s_snapshot
{
	t_history	state;
	t_cam		cam;
	t_entity	entity;
}	t_snapshot;

typedef struct s_asset
{
	t_tex		wall_base[WALL_DIR_COUNT];
	int			rgb[BACKGROUND_COUNT];
	t_tex_seq	background[BACKGROUND_COUNT];
	t_tex_seq	wall_deco;
	t_tex		wall_goal;
	t_tex		door[DOOR_COUNT][SLOT_COUNT];
	t_tex_seq	hand_idle;
	t_tex_seq	hand_shot[SLOT_COUNT];
	t_tex_seq	overlay_damage;
	t_tex_seq	hud;
	t_tex		item_goal;
	t_tex_seq	item_heal[SLOT_COUNT];
	t_tex_seq	item_gear[SLOT_COUNT];
	t_tex		props[SLOT_COUNT];
	t_tex_seq	mobs[MOB_COUNT][SLOT_COUNT];
}	t_asset;

typedef struct s_cache
{
	t_ceil_anim		ceil;
	t_door_shape	door_shape[SLOT_COUNT];
	double			prop_half[SLOT_COUNT];
}	t_runtime;

typedef struct s_game
{
	t_scene		scene;
	t_cam		cam;
	t_asset		asset;
	t_runtime	runtime;
	t_entity	entity;
	t_history	state;
	t_hud		hud;
	t_snapshot	snapshot;
}	t_game;

typedef struct s_core
{
	void	*mlx;
	void	*win;
	t_img	screen;
	t_img	display;
	t_game	games[GAME_MAX];
	t_idx	curr_game;
	t_num	game_count;
}	t_core;

typedef struct s_app_assets
{
	t_img	font[FONT_COUNT];
	t_img	intro_title;
	t_img	intro_rules;
	t_img	button[BUTTON_COUNT][TOGGLE_COUNT];
	t_img	prologue[PROL_COUNT];
	t_img	outro_fail;
	t_img	outro_clear;
	t_img	outro_score;
	t_img	mini_hero;
	t_img	mini_box;
}	t_app_assets;

typedef struct s_screen
{
	struct s_dissolve
	{
		t_idx	mode;
		double	started_at;
	}	dissolve;
	t_idx	prologue;
	t_bool	hover[2];
}	t_screen;

typedef struct s_input
{
	t_bool	keys[KEY_COUNT];
	t_ixy	mouse;
	t_bool	mouse_drag;
	t_pos	last_mouse_x;
	t_bool	mouse_inside;
}	t_input;

typedef struct s_rend
{
	double		*depth;
	t_ray_hit	hit;
}	t_rend;

typedef struct s_app
{
	t_core			core;
	t_input			input;
	t_rend			rend;
	t_app_assets	assets;
	t_screen		screen;
}	t_app;

/* Entry */
int			main(int argc, char **argv);
void		open_app(int argc, char **argv, t_app *app);
int			open_cub(char *path, t_game *game);
int			load_cub(t_game *game, int fd);
int			close_app(t_app *app);

/* Parse */
const char	**required_ids(void);
int			is_valid_id(char *line, const char *id);
int			is_valid_sign(char tile);
int			is_valid_premap(t_game *game);
int			is_walkable_sign(char tile);
int			is_zone_sign(char c);
int			is_door_sign(char tile);
int			is_wall_sign(char tile);
int			is_closed_map(t_game *game);
int			is_in_map(t_game *game, t_pos x, t_pos y);
char		get_tile(t_game *game, t_pos x, t_pos y);
int			is_walkable_tile(t_game *game, t_ixy tile);
int			parse_premap(t_game *game, char *line, t_vec *lines);
int			parse_wall(t_game *game, char *line, const char **wall);
int			parse_background(t_game *game, char *line, const char **surface);
int			parse_color(t_game *game, char *line, t_idx type);
int			parse_map(t_game *game, char *row, t_vec *lines);

/* Init */
int			init_mlx(t_core *core);
void		init_app(t_app *app, t_game *game);
int			load_xpm_image(t_app *app, char *path, t_img *tex);
int			load_wall(t_app *app, t_game *game);

/* Render */
void		rend_app(t_app *app, t_game *game);
void		draw_screen(t_app *app);
void		draw_window(t_app *app);
void		draw_rect(t_app *app, t_rect rect, int color);
void		put_pixel(t_img *img, t_ixy pos, int color);
int			get_pixel(t_img *img, t_ixy pos);
int			get_scaled_pixel(t_img *img, t_ixy pos, t_dim width, t_dim height);
int			is_transparent_color(int color);
void		init_ray(t_ray *ray, t_game *game, t_pos x);
int			collect_wallfaces(t_game *game, t_ray_hit hit);
void		draw_wall(t_app *app, t_game *game, t_pos x);
void		draw_wallface(t_app *app, t_game *game, t_ray_hit hit, t_pos x);
void		draw_wallfaces(t_app *app, t_game *game, t_num count, t_pos x);

/* Runtime */
void		exec_app(t_app *app);
void		exec_hero(t_app *app, t_game *game);
int			key_release(int keycode, t_app *app);
int			get_key_idx(int keycode);
int			key_press(int keycode, t_app *app);
void		move_forward(t_game *game, double speed);
void		move_backward(t_game *game, double speed);
void		strafe_left(t_game *game, double speed);
void		strafe_right(t_game *game, double speed);
void		rotate_left(t_game *game, double rot);
void		rotate_right(t_game *game, double rot);
int			is_box_overlap(t_box a, t_box b);
int			overlap_wall(t_game *game, t_box actor);
int			is_hero_blocked(t_game *game, double x, double y);

/* Utility */
char		*ft_strpbrk(const char *str, const char *accept);
char		*ft_strskip(char *str, int (*ft)(char), int invert);
int			ft_isspace(char c);
int			min(int a, int b);
int			max(int a, int b);
t_idx		get_id_idx(const char **array, const char *target);
int			put_err(char *type, char *message);
int			put_load_err(const char *kind, char *path);
void		free_split(char **arr);
void		free_str(void *elem);
void		destroy_img(void *mlx, t_img *img);
void		destroy_image(void *mlx, t_img *img);
void		destroy_mlx(t_core *core);
void		free_cub(t_app *app, t_game *game);
void		destroy_app(t_app *app);
#endif
