NAME=lem-in
SRC=main.c lem-in.c nest.c utility.c
OBJ=$(SRC:%.c=%.o)
CC=gcc
CFLAGS=-Wall -Wextra -Werror

all: $(NAME)

$(NAME) : $(OBJ)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all