CFLAG = -Wall -Wextra -Werror -g
B_SIZE = -D BUFFER_SIZE=10000
NAME = get_library.a
SRC = get_next_line.c get_next_line_utils.c

OBJ = $(SRC:.c=.o)

all : $(NAME) compile

$(NAME) : $(OBJ)
	ar rcs $(NAME) $(OBJ)

compile :
	gcc $(CFLAG) $(B_SIZE) main/main.c $(NAME) && ./a.out

.c.o :
	gcc $(CFLAG) $(B_SIZE) -I . -o $@ -c $<

clean :
	rm -fr $(OBJ)

fclean : clean
	rm $(NAME)

re : fclean all
