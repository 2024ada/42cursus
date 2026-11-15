CC = cc
CFLAGS = -Wall -Wextra -Werror

NAME = pipex

LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

GNL_DIR = get_next_line
GNL_SRCS = $(GNL_DIR)/get_next_line.c $(GNL_DIR)/get_next_line_utils.c

SRCS = pipex.c \
	set_file.c \
	set_pid.c \
	run_pid.c \
	get_cmd.c \
	cut_cmd.c \
	$(GNL_SRCS)

OBJS = $(SRCS:.c=.o)

INCLUDES = -I$(LIBFT_DIR) -I$(GNL_DIR)

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) -o $@ $(OBJS) $(LIBFT)

bonus: all

$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR)

%.o: %.c pipex.h
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f $(OBJS)
	@$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re bonus
