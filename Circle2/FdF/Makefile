CC = cc
CFLAGS = -Wall -Wextra -Werror

NAME = fdf

MANDATORY_DIR = mandatory
BONUS_DIR = bonus
LIBFT_DIR = libft
FT_PRINTF_DIR = ft_printf
GNL_DIR = get_next_line
MLX_DIR = minilibx-linux

SRCS = $(MANDATORY_DIR)/fdf.c \
		$(MANDATORY_DIR)/fdf_map.c \
		$(MANDATORY_DIR)/fdf_input.c \
		$(MANDATORY_DIR)/fdf_raw.c \
		$(MANDATORY_DIR)/fdf_grid.c \
		$(MANDATORY_DIR)/fdf_init.c \
		$(MANDATORY_DIR)/fdf_view.c \
		$(MANDATORY_DIR)/fdf_window.c \
		$(MANDATORY_DIR)/fdf_menu.c \
		$(MANDATORY_DIR)/fdf_text.c \
		$(MANDATORY_DIR)/fdf_transform.c \
		$(MANDATORY_DIR)/fdf_isometric.c \
		$(MANDATORY_DIR)/fdf_motion.c \
		$(MANDATORY_DIR)/fdf_action.c \
		$(MANDATORY_DIR)/fdf_line.c \
		$(MANDATORY_DIR)/fdf_image.c \
		$(MANDATORY_DIR)/fdf_palette.c \
		$(MANDATORY_DIR)/fdf_color.c \
		$(MANDATORY_DIR)/fdf_font.c \
		$(MANDATORY_DIR)/fdf_event.c \
		$(MANDATORY_DIR)/fdf_hook.c \
		$(MANDATORY_DIR)/fdf_popup.c \
		$(MANDATORY_DIR)/fdf_output.c \
		$(MANDATORY_DIR)/fdf_save.c \
		$(MANDATORY_DIR)/fdf_free.c \
		$(MANDATORY_DIR)/fdf_utils.c \
		$(MANDATORY_DIR)/fdf_glyphs00.c \
		$(MANDATORY_DIR)/fdf_glyphs01.c \
		$(MANDATORY_DIR)/fdf_glyphs02.c \
		$(MANDATORY_DIR)/fdf_glyphs03.c \
		$(MANDATORY_DIR)/fdf_glyphs04.c \
		$(MANDATORY_DIR)/fdf_glyphs05.c \
		$(MANDATORY_DIR)/fdf_glyphs06.c \
		$(MANDATORY_DIR)/fdf_widgets00.c \
		$(MANDATORY_DIR)/fdf_widgets01.c \
		$(MANDATORY_DIR)/fdf_widgets02.c \
		$(MANDATORY_DIR)/fdf_widgets03.c \
		$(MANDATORY_DIR)/fdf_widgets04.c \
		$(MANDATORY_DIR)/fdf_widgets05.c \
		$(MANDATORY_DIR)/fdf_widgets06.c \
		$(MANDATORY_DIR)/fdf_widgets07.c \
		$(MANDATORY_DIR)/fdf_widgets08.c \
		$(MANDATORY_DIR)/fdf_widgets09.c \
		$(MANDATORY_DIR)/fdf_widgets10.c \
		$(MANDATORY_DIR)/fdf_widgets11.c \
		$(MANDATORY_DIR)/fdf_widgets12.c \
		$(GNL_DIR)/get_next_line.c \
		$(GNL_DIR)/get_next_line_utils.c

BONUS_SRCS = $(BONUS_DIR)/fdf_bonus.c \
		$(BONUS_DIR)/fdf_map_bonus.c \
		$(BONUS_DIR)/fdf_input_bonus.c \
		$(BONUS_DIR)/fdf_raw_bonus.c \
		$(BONUS_DIR)/fdf_grid_bonus.c \
		$(BONUS_DIR)/fdf_init_bonus.c \
		$(BONUS_DIR)/fdf_view_bonus.c \
		$(BONUS_DIR)/fdf_window_bonus.c \
		$(BONUS_DIR)/fdf_menu_bonus.c \
		$(BONUS_DIR)/fdf_text_bonus.c \
		$(BONUS_DIR)/fdf_transform_bonus.c \
		$(BONUS_DIR)/fdf_isometric_bonus.c \
		$(BONUS_DIR)/fdf_motion_bonus.c \
		$(BONUS_DIR)/fdf_action_bonus.c \
		$(BONUS_DIR)/fdf_line_bonus.c \
		$(BONUS_DIR)/fdf_image_bonus.c \
		$(BONUS_DIR)/fdf_palette_bonus.c \
		$(BONUS_DIR)/fdf_color_bonus.c \
		$(BONUS_DIR)/fdf_font_bonus.c \
		$(BONUS_DIR)/fdf_event_bonus.c \
		$(BONUS_DIR)/fdf_hook_bonus.c \
		$(BONUS_DIR)/fdf_popup_bonus.c \
		$(BONUS_DIR)/fdf_output_bonus.c \
		$(BONUS_DIR)/fdf_save_bonus.c \
		$(BONUS_DIR)/fdf_free_bonus.c \
		$(BONUS_DIR)/fdf_utils_bonus.c \
		$(BONUS_DIR)/fdf_glyphs00_bonus.c \
		$(BONUS_DIR)/fdf_glyphs01_bonus.c \
		$(BONUS_DIR)/fdf_glyphs02_bonus.c \
		$(BONUS_DIR)/fdf_glyphs03_bonus.c \
		$(BONUS_DIR)/fdf_glyphs04_bonus.c \
		$(BONUS_DIR)/fdf_glyphs05_bonus.c \
		$(BONUS_DIR)/fdf_glyphs06_bonus.c \
		$(BONUS_DIR)/fdf_widgets00_bonus.c \
		$(BONUS_DIR)/fdf_widgets01_bonus.c \
		$(BONUS_DIR)/fdf_widgets02_bonus.c \
		$(BONUS_DIR)/fdf_widgets03_bonus.c \
		$(BONUS_DIR)/fdf_widgets04_bonus.c \
		$(BONUS_DIR)/fdf_widgets05_bonus.c \
		$(BONUS_DIR)/fdf_widgets06_bonus.c \
		$(BONUS_DIR)/fdf_widgets07_bonus.c \
		$(BONUS_DIR)/fdf_widgets08_bonus.c \
		$(BONUS_DIR)/fdf_widgets09_bonus.c \
		$(BONUS_DIR)/fdf_widgets10_bonus.c \
		$(BONUS_DIR)/fdf_widgets11_bonus.c \
		$(BONUS_DIR)/fdf_widgets12_bonus.c \
		$(GNL_DIR)/get_next_line.c \
		$(GNL_DIR)/get_next_line_utils.c

OBJS = $(SRCS:.c=.o)
BONUS_OBJS = $(BONUS_SRCS:.c=.o)

LIBFT = $(LIBFT_DIR)/libft.a
FT_PRINTF = $(FT_PRINTF_DIR)/libftprintf.a
MLX_LIB = $(MLX_DIR)/libmlx.a

INCLUDES = -I$(MANDATORY_DIR) -I$(BONUS_DIR) -I$(LIBFT_DIR) -I$(FT_PRINTF_DIR) -I$(GNL_DIR) -I$(MLX_DIR)

MLX_LINK = -L$(MLX_DIR) -lmlx -lXext -lX11
MATH_LINK = -lm

all: $(LIBFT) $(FT_PRINTF) $(MLX_LIB) $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(FT_PRINTF) $(MLX_LIB) $(MLX_LINK) $(MATH_LINK) -o $(NAME)

bonus: $(LIBFT) $(FT_PRINTF) $(MLX_LIB) $(BONUS_OBJS)
	$(CC) $(CFLAGS) $(BONUS_OBJS) $(LIBFT) $(FT_PRINTF) $(MLX_LIB) $(MLX_LINK) $(MATH_LINK) -o $(NAME)

$(MANDATORY_DIR)/%.o: $(MANDATORY_DIR)/%.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(BONUS_DIR)/%.o: $(BONUS_DIR)/%.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(GNL_DIR)/%.o: $(GNL_DIR)/%.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

$(FT_PRINTF): $(LIBFT)
	$(MAKE) -C $(FT_PRINTF_DIR)

$(MLX_LIB):
	cd $(MLX_DIR) && ./configure

clean:
	$(MAKE) -C $(LIBFT_DIR) clean
	$(MAKE) -C $(FT_PRINTF_DIR) clean
	$(MAKE) -C $(MLX_DIR) clean
	rm -f $(OBJS) $(BONUS_OBJS)

fclean: clean
	$(MAKE) -C $(LIBFT_DIR) fclean
	$(MAKE) -C $(FT_PRINTF_DIR) fclean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re bonus