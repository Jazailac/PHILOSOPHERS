NAME = philo
CC = cc
CFLAGS = -Wall -Wextra -Werror -pthread

SRCS = main.c init.c routine.c monitor.c utils.c getters_setters.c
OBJS = $(SRCS:.c=.o)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS)

all: $(NAME)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

