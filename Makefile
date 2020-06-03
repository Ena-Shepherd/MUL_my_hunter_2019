##
## EPITECH PROJECT, 2019
## zdf
## File description:
## qsdf
##

SRC	=	my_putchar.c \
		my_putstr.c \

		

OBJ	=	$(SRC:.c=.o)

NAME	=	libmy.a

lib:	
	./sh.sh mains.c

$(NAME):	$(OBJ)
	gcc -o $(NAME) $(OBJ) -g3 -g

clean:
	rm -f $(OBJ)

fclean:
	rm -f my_hunter

re:	fclean
	./sh.sh mains.c
	
