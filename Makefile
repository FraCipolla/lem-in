NAME=lem-in
NAME2=visua-hex
SRC=main.c lem-in.c nest.c utility.c
SRC2=lem-in.c visualizer.c utility.c
OBJ=$(SRC:%.c=%.o)
OBJ2=$(SRC2:%.c=%.o)
CC=gcc
CFLAGS=-Wall -Wextra -Werror

all: $(NAME) $(NAME2)

$(NAME) : $(OBJ)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ)

$(NAME2) : $(OBJ2)
	$(CC) $(CFLAGS) -o $(NAME2) $(OBJ2)

clean:
	rm -f $(OBJ) $(OBJ2)

fclean: clean
	rm -f $(NAME) $(NAME2)

re: fclean all