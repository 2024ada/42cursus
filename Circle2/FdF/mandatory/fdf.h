/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ucho <ucho@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 15:13:23 by ucho              #+#    #+#             */
/*   Updated: 2025/08/19 16:57:49 by ucho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "../libft/libft.h"
# include "../get_next_line/get_next_line.h"
# include "../ft_printf/ft_printf.h"
# include "../minilibx-linux/mlx.h"
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <math.h>
# include <stdio.h>

# define KEY_COUNT 17
# define KEY_ESC 65307
# define KEY_UP 65362
# define KEY_DOWN 65364
# define KEY_LEFT 65361
# define KEY_RIGHT 65363
# define KEY_PLUS 61
# define KEY_MINUS 45
# define KEY_W 119
# define KEY_S 115
# define KEY_A 97
# define KEY_D 100
# define KEY_Q 113
# define KEY_E 101
# define KEY_R 114
# define KEY_I 105
# define KEY_O 111
# define KEY_P 112

# define WIN_W 1920
# define WIN_H 1080
# define MAP_W 1545
# define MAP_H 1005
# define MAP_X 375
# define MAP_Y 75

# define GLYPHS_COUNT 95
# define WIDGETS_COUNT 59
# define CATEGORY_COUNT 5
# define MENU_COUNT 12

# define ISOMETRIC 1
# define ORTHOGRAPHIC 0
# define TRUE 1
# define FALSE 0

# define DEGREE_30 0.523599
# define M_PI 3.14159265358979323846
# define WHITE 0xffffff
# define INT_MIN -2147483648
# define INT_MAX 2147483647

typedef struct s_raw
{
	char			**strs;
	int				width;
	struct s_raw	*next;
}	t_raw;

typedef struct s_xpm
{
	char			*key;
	unsigned int	color;
	struct s_xpm	*next;	
}	t_xpm;

typedef struct s_point
{
	float			x;
	float			y;
	float			z;
	unsigned int	color;
}	t_point;

typedef struct s_map
{
	t_raw		*raw;
	t_point		**grid;
	int			width;
	int			height;
	long long	depth;
	int			projection;
}	t_map;

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
	int		width;
	int		height;
	int		ascii;
}	t_img;

typedef struct s_key
{
	int	code;
	int	is_pressed;
}	t_key;

typedef struct s_view
{
	float	scale;
	float	scale_max;
	float	scale_min;
	int		ofs_x;
	int		ofs_y;
	int		ofs_max_x;
	int		ofs_max_y;
	float	rot_x;
	float	rot_y;
	float	rot_z;
	float	min_x;
	float	max_x;
	float	min_y;
	float	max_y;
	float	mid_x;
	float	mid_y;
}	t_view;

typedef struct s_file
{
	char	*name;
	int		screenshot;
}	t_file;

typedef struct s_gui
{
	char	*menu[MENU_COUNT];
	char	*highlight[2];
	int		hover[MENU_COUNT];
	int		layout[CATEGORY_COUNT + 1];
	int		popup[4];
	int		exit[3];
}	t_gui;

typedef struct s_mlx
{
	void	*ctx;
	void	*win;
	t_img	img;
}	t_mlx;

typedef struct s_info
{
	int		x;
	int		y;
	int		width;
	int		height;
	void	*data;
}	t_info;

typedef struct s_color
{
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;
}	t_color;

typedef struct s_meta
{
	int	width;
	int	height;
	int	size;
	int	cpp;
}	t_meta;

typedef struct s_fdf
{
	t_map		map;
	t_mlx		mlx;
	const char	**glyphs[GLYPHS_COUNT];
	t_img		widgets[WIDGETS_COUNT];
	t_key		keys[KEY_COUNT];
	t_view		view;
	t_gui		gui;
	t_file		file;
}	t_fdf;

typedef const char	**(*t_widget)(void);

void			set_fdf(t_fdf *fdf);
void			put_fdf(t_fdf *fdf);
void			run_fdf(t_fdf *fdf);
void			set_map(t_map *map, char *name);
t_raw			*get_raw(t_map *map, char *name);
int				set_input(char *name);
t_point			**get_grid(t_map *map);
void			set_mlx(t_mlx *mlx, t_map map);
void			set_widgets(t_fdf *fdf, t_map map);
const char		***set_glyphs(const char ***glyphs);
void			set_keys(t_key *keys);
void			set_view(t_fdf *fdf);
void			set_gui(t_fdf *fdf);
void			put_top(t_fdf *fdf);
void			put_side(t_fdf *fdf);
void			put_map(t_fdf *fdf);
void			put_win(t_mlx mlx);
void			del_map(t_img *img);
int				key_press(int keycode, void *param);
int				key_release(int keycode, void *param);
int				mouse_move(int x, int y, void *param);
int				mouse_click(int button, int x, int y, void *param);
int				get_key(t_fdf *fdf, int code);
int				close_hook(void *param);
int				loop_hook(void *param);
void			mlx_pixel_to_image(t_img *img, int x, int y,
					unsigned int color);
void			*mlx_xpm_array_to_image(void *mlx, char **xpm);
void			put_panel(t_img *img, t_info info);
void			put_xpm(t_img *dst, t_info info);
t_xpm			*parse_palette(char **xpm, int colors, int cpp);
unsigned int	get_color(char *symbol, t_xpm *map, int cpp);
void			put_xpm_pixels(t_img *img, t_xpm *map, char **xpm, int cpp);
int				parse_meta(char **xpm, t_meta *meta);
unsigned int	str_to_hex(const char *hex);
char			*hex_to_str(unsigned int color);
unsigned int	rgb_to_hex(t_color c);
t_color			hex_to_rgb(unsigned int hex);
t_point			set_scale(t_point point, float factor);
t_point			set_rotate_x(t_point point, float angle);
t_point			set_rotate_y(t_point point, float angle);
t_point			set_rotate_z(t_point point, float angle);
t_point			set_translate(t_point point, int dx, int dy);
t_point			set_transform(t_point point, t_fdf *fdf);
void			set_isometric(int state, float *x, float *y, float z);
void			put_menus(t_fdf *fdf, t_img *xpm, t_gui gui);
void			run_scaling(t_fdf *fdf, int button);
void			run_translation(t_fdf *fdf, int button);
void			run_rotation(t_fdf *fdf, int button);
void			run_capture(t_fdf *fdf, int button);
void			run_projection(t_fdf *fdf, int button);
void			run_exit(t_fdf *fdf, int button);
void			run_popup(t_fdf *fdf, int button);
unsigned int	get_pixel_color(t_img *img, int x, int y);
char			**get_glyphs(const char **xpm,
					unsigned int fg, unsigned int bg);
void			put_glyphs(t_fdf *fdf, char *str, t_info info);
void			put_exit(t_fdf *fdf);
void			put_popup(t_fdf *fdf);
void			put_alert(t_fdf *fdf);
void			put_line(t_point start, t_point end, t_fdf *fdf);
char			*get_ppm_name(t_file file);
void			save_ppm(t_file file, t_img img);
void			free_matrix(void *row, size_t offset);
void			free_raw(t_raw *raw);
void			free_palette(t_xpm *map);
void			free_input(int fd);
int				put_error(const char *message);
long long		ft_atoll(const char *nptr);
void			glyphs00(const char ***glyphs);
void			glyphs01(const char ***glyphs);
void			glyphs02(const char ***glyphs);
void			glyphs03(const char ***glyphs);
void			glyphs04(const char ***glyphs);
void			glyphs05(const char ***glyphs);
void			glyphs06(const char ***glyphs);
void			glyphs07(const char ***glyphs);
void			glyphs08(const char ***glyphs);
void			glyphs09(const char ***glyphs);
void			glyphs10(const char ***glyphs);
void			glyphs11(const char ***glyphs);
void			glyphs12(const char ***glyphs);
void			glyphs13(const char ***glyphs);
void			glyphs14(const char ***glyphs);
void			glyphs15(const char ***glyphs);
void			glyphs16(const char ***glyphs);
void			glyphs17(const char ***glyphs);
void			glyphs18(const char ***glyphs);
void			glyphs19(const char ***glyphs);
void			glyphs20(const char ***glyphs);
void			glyphs21(const char ***glyphs);
void			glyphs22(const char ***glyphs);
void			glyphs23(const char ***glyphs);
void			glyphs24(const char ***glyphs);
void			glyphs25(const char ***glyphs);
void			glyphs26(const char ***glyphs);
void			glyphs27(const char ***glyphs);
void			glyphs28(const char ***glyphs);
void			glyphs29(const char ***glyphs);
void			glyphs30(const char ***glyphs);
void			glyphs31(const char ***glyphs);
void			glyphs32(const char ***glyphs);
const char		**widget00(void);
const char		**widget01(void);
const char		**widget02(void);
const char		**widget03(void);
const char		**widget04(void);
const char		**widget05(void);
const char		**widget06(void);
const char		**widget07(void);
const char		**widget08(void);
const char		**widget09(void);
const char		**widget10(void);
const char		**widget11(void);
const char		**widget12(void);
const char		**widget13(void);
const char		**widget14(void);
const char		**widget15(void);
const char		**widget16(void);
const char		**widget17(void);
const char		**widget18(void);
const char		**widget19(void);
const char		**widget20(void);
const char		**widget21(void);
const char		**widget22(void);
const char		**widget23(void);
const char		**widget24(void);
const char		**widget25(void);
const char		**widget26(void);
const char		**widget27(void);
const char		**widget28(void);
const char		**widget29(void);
const char		**widget30(void);
const char		**widget31(void);
const char		**widget32(void);
const char		**widget33(void);
const char		**widget34(void);
const char		**widget35(void);
const char		**widget36(void);
const char		**widget37(void);
const char		**widget38(void);
const char		**widget39(void);
const char		**widget40(void);
const char		**widget41(void);
const char		**widget42(void);
const char		**widget43(void);
const char		**widget44(void);
const char		**widget45(void);
const char		**widget46(void);
const char		**widget47(void);
const char		**widget48(void);
const char		**widget49(void);
const char		**widget50(void);
const char		**widget51(void);
const char		**widget52(void);
const char		**widget53(void);
const char		**widget54(void);
const char		**widget55(void);
const char		**widget56(void);
const char		**widget57(void);
const char		**widget58(void);

#endif