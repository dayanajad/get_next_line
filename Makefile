NAME	=	get_next_line.a
CC		=	cc
CFLAGS	=	-Wall -Wextra -Werror
AR		= 	ar rcs
RM		=	rm -f

SRC		=	get_next_line.c get_next_line_utils.c
OBJ		=	$(SRC:.c=.o)

$(NAME): $(OBJ)
	$(AR) $(NAME) $(OBJ)

all: $(NAME)

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
