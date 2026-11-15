CC		= cc
CFLAGS	= -Wall -Wextra -Werror -pthread
NAME	= philo

SRCS	= philo.c \
		philo_set.c \
		philo_run.c \
		philo_let.c \
		philo_sim.c \
		philo_ths.c \
		philo_mtx.c \
		philo_time.c \
		philo_check.c \
		philo_msg.c \
		philo_utils.c

OBJS	= $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re