SRCSERV		=	src/server.c src/servfuncs.c

OBJSERV		=	${SRCSERV:.c=.o}

INCLUDE		=	includes/minitalk.h

SRCCLNT		=	src/client.c src/ft_atoi.c

OBJCLNT		=	${SRCCLNT:.c=.o}

CC			=	gcc

CFLAGS		=	-Wall -Werror -Wextra

RM			=	rm -f

NAME		=	minitalk

SENAME		=	server

CLNAME		=	client

%o:			%c Makefile ${INCLUDE}
			${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

all:		$(NAME)

$(NAME):	${OBJSERV} ${OBJCLNT} Makefile ${INCLUDE}
			${CC} ${CFLAGS} ${OBJSERV} -o ${SENAME}
			${CC} ${CFLAGS} ${OBJCLNT} -o ${CLNAME}

clean:
			${RM} ${OBJSERV} ${OBJCLNT}

fclean:		clean
			${RM} ${SENAME} ${CLNAME}

re:			fclean all

.PHONY:		all clean fclean re
