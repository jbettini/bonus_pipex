NAME = libft.a

SRCS	=	${wildcard *.c}	

CC = gcc
RM = rm -f
AR = ar rcs

OBJS = ${SRCS:.c=.o}

CFLAGS = -Wall -Wextra -Werror

%.o: %.c
		${CC} ${CFLAGS} -o $@ -c $?

${NAME}:	${OBJS}	
			${AR} ${NAME} ${OBJS}


all:	${NAME} 

clean:
	${RM} ${OBJS}

fclean:	clean
		${RM} ${NAME}

re:	fclean all


.PHONY: all clean fclean re
