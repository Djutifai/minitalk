SRCSERV		=	src/server.c src/servfuncs.c src/commonfncs.c

OBJSERV		=	${SRCSERV:.c=.o}

INCLUDE		=	includes/

SRCCLNT		=	src/client.c src/clfuncs.c src/commonfncs.c

OBJCLNT		=	${SRCCLNT:.c=.o}

SRCSERVBON	=	src/server_bonus.c src/servfuncs_bonus.c src/commonfncs_bonus.c

OBJSERVBON	=	${SRCSERVBON:.c=.o}

SRCCLNTBON	=	src/client_bonus.c src/clfuncs_bonus.c src/commonfncs_bonus.c

OBJCLNTBON	=	${SRCCLNTBON:.c=.o}

CC			=	gcc

CFLAGS		=	-Wall -Werror -Wextra

RM			=	rm -f

NAME		=	minitalk

NAMEBON		=	minitalk_bonus

SENAME		=	server

CLNAME		=	client

SENAMEBON	=	server_bonus

CLNAMEBON	=	client_bonus

%.o:			%.c ${INCLUDE} Makefile 
				${CC} ${CFLAGS} -c $< -o $@ -I ${INCLUDE}

all:			$(NAME)

$(NAME):		Makefile ${INCLUDE} $(CLNAME) $(SENAME)


$(CLNAME):		${OBJCLNT}
				${CC} ${CFLAGS} ${OBJCLNT} -o ${CLNAME}

$(SENAME):		${OBJSERV}
				${CC} ${CFLAGS} ${OBJSERV} -o ${SENAME}
clean:
				${RM} ${OBJSERV} ${OBJCLNT}

fclean:			clean
				${RM} ${SENAME} ${CLNAME}

re:				fclean all


bonus:			$(NAMEBON)

$(NAMEBON):		Makefile ${INCLUDE} $(CLNAMEBON) $(SENAMEBON) 

$(SENAMEBON):	${OBJSERVBON}
				${CC} ${CFLAGS} ${OBJSERVBON} -o ${SENAMEBON}

$(CLNAMEBON):	${OBJCLNTBON}
				${CC} ${CFLAGS} ${OBJCLNTBON} -o ${CLNAMEBON}

cleanbonus:
				${RM} ${OBJSERVBON} ${OBJCLNTBON}

fcleanbonus:	cleanbonus
				${RM} ${SENAMEBON} ${CLNAMEBON}

rebonus:		fcleanbonus bonus

.PHONY:			${NAME} all clean fclean re ${NAMEBON} bonus cleanbonus fcleanbonus rebonus 
