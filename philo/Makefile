CC = cc
CFLAGS = -Wall -Wextra -Werror
NAME = philo

SRC = main.c utils.c init.c thread.c helper.c manager.c
OBJ = $(SRC:.c=.o)

all : $(NAME)

%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME) : $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

clean :
	rm -rf $(OBJ)

fclean :
	rm -rf $(OBJ)
	rm -rf $(NAME)

re : fclean all

.Phony : all clean fclean re

