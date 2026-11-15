CC		= cc
CFLAGS	= -Wall -Wextra -Werror -pthread
NAME	= philo_bonus

SRCS	= philo_bonus.c \
		philo_set_bonus.c \
		philo_run_bonus.c \
		philo_let_bonus.c \
		philo_sim_bonus.c \
		philo_sem_bonus.c \
		philo_time_bonus.c \
		philo_check_bonus.c \
		philo_msg_bonus.c \
		philo_utils_bonus.c

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