NAME		= libft.a

CC			= cc
CFLAGS		= -Wall -Wextra -Werror
CPPFLAGS	= -I.

BUILD_DIR	= build
SRCS		= $(sort $(wildcard *.c))
OBJS		= $(SRCS:%.c=$(BUILD_DIR)/%.o)
DEPS		= $(OBJS:.o=.d)

all: $(NAME)

$(NAME): $(OBJS)
	ar rcs $@ $^

$(BUILD_DIR)/%.o: %.c Makefile | $(BUILD_DIR)
	$(CC) $(CFLAGS) $(CPPFLAGS) -MMD -MP -c $< -o $@

$(BUILD_DIR):
	mkdir -p $@

clean:
	rm -rf $(BUILD_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

-include $(DEPS)

.PHONY: all clean fclean re
