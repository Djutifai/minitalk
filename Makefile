SRCSERV		=	src/server.c src/servfuncs.c

OBJSERV		=	${SRCSERV:.c=.o}

INCLUDE		=	includes/minitalk.h

SRCCLNT		=	src/client.c src/clfuncs.c

OBJCLNT		=	${SRCCLNT:.c=.o}

SRCSERVBON	=	src/server_bonus.c src/servfuncs_bonus.c

OBJSERVBON	=	${SRCSERVBON:.c=.o}

INCLUDEBON	=	includes/minitalk_bonus.h

SRCCLNTBON	=	src/client_bonus.c src/clfuncs_bonus.c

OBJCLNTBON	=	${SRCCLNTBON:.c=.o}

CC			=	gcc

CFLAGS		=	-Wall -Werror -Wextra

RM			=	rm -f

NAME		=	minitalk

SENAME		=	server

CLNAME		=	client

SENAMEBON	=	server_bonus

CLNAMEBON	=	client_bonus

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

bonus:		${OBJSERVBON} ${OBJCLNTBON} Makefile ${INCLUDEBON}
			${CC} ${CFLAGS} ${OBJSERVBON} -o ${SENAMEBON}
			${CC} ${CFLAGS} ${OBJCLNTBON} -o ${CLNAMEBON}

cleanbonus:
			${RM} ${OBJSERVBON} ${OBJCLNTBON}

fcleanbonus:cleanbonus
			${RM} ${SENAMEBON} ${CLNAMEBON}

rebonus:	fcleanbonus bonus

.PHONY:		all clean fclean re
