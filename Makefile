NAME = philo
CC = cc
FLAGS = -Wall -Wextra -Werror

SRC = main.c \
	  parsing.c \
	  philo.c \
	  utils.c \
	  init.c \
	  actions.c \
	  supervisor.c 

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(FLAGS) $(OBJ) -o $(NAME)

%.o: %.c
	$(CC) $(FLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
