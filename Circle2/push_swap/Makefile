CC = cc
CFLAGS = -Wall -Wextra -Werror

NAME = push_swap
BONUS_NAME = checker

LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

FT_PRINTF_DIR = ft_printf
FT_PRINTF = $(FT_PRINTF_DIR)/libftprintf.a

GNL_DIR = get_next_line
GNL_SRCS = $(GNL_DIR)/get_next_line.c $(GNL_DIR)/get_next_line_utils.c

SRCS = push_swap.c \
	push_swap_utils.c \
	push_swap_args.c \
	push_swap_parse.c \
	push_swap_sort.c \
	push_swap_lis.c \
	push_swap_cost.c \
	push_swap_ops.c \
	push_swap_ops_extra.c

BONUS_SRCS = checker.c \
	push_swap_utils.c \
	push_swap_args.c \
	push_swap_parse.c \
	push_swap_sort.c \
	push_swap_lis.c \
	push_swap_cost.c \
	push_swap_ops.c \
	push_swap_ops_extra.c \
	$(GNL_SRCS)

OBJS = $(SRCS:.c=.o)
BONUS_OBJS = $(BONUS_SRCS:.c=.o)

INCLUDES = -I$(LIBFT_DIR) -I$(FT_PRINTF_DIR) -I$(GNL_DIR)

all: $(LIBFT) $(FT_PRINTF) $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(INCLUDES) $(OBJS) $(LIBFT) $(FT_PRINTF) -o $(NAME)

bonus: $(LIBFT) $(FT_PRINTF) $(BONUS_NAME)

$(BONUS_NAME): $(BONUS_OBJS)
	$(CC) $(CFLAGS) $(INCLUDES) $(BONUS_OBJS) $(LIBFT) $(FT_PRINTF) -o $(BONUS_NAME)

$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR)

$(FT_PRINTF):
	@$(MAKE) -C $(FT_PRINTF_DIR)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f $(OBJS) $(BONUS_OBJS)
	@$(MAKE) -C $(LIBFT_DIR) clean
	@$(MAKE) -C $(FT_PRINTF_DIR) clean

fclean: clean
	rm -f $(NAME) $(BONUS_NAME) $(LIBFT) $(FT_PRINTF)
	@$(MAKE) -C $(FT_PRINTF_DIR) fclean

re: fclean all

.PHONY: all bonus clean fclean re
