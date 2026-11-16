CC = cc
CFLAGS = -Wall -Wextra -Werror

NAME = libftprintf.a

LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

SRCS = ft_printf.c ft_printf_utils.c ft_printf_c.c ft_printf_s.c ft_printf_p.c ft_printf_d.c ft_printf_u.c ft_printf_x.c ft_printf_bonus.c ft_printf_utils_bonus.c
OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	cp $(LIBFT) $(NAME)
	ar rcs $(NAME) $(OBJS)

bonus: all

$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR)

%.o: %.c ft_printf.h
	$(CC) $(CFLAGS) -I$(LIBFT_DIR) -c $< -o $@

clean:
	rm -f $(OBJS)
	@$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re bonus