
NAME	=	philo

HEADER	=	${SRC_DIR}/philo.h

SRC_F	=	philo.c	get_arguments_funcs.c	simulation_funcs.c	philo_utils.c \
			watch_funcs.c

SRC_DIR	=	./srcs

SRCS	=	$(addprefix ${SRC_DIR}/,${SRC_F})

OBJS	=	${SRCS:.c=.o}

CC		=	cc

CFLAGS	=	-Wall -Werror -Wextra

%.o			:	%.c ${HEADER}
				${CC} ${CFLAGS} $< -c -o $@

.PHONY		:	all re clean fclean debug run

${NAME}		:	${OBJS}
				${CC} ${CFLAGS} ${OBJS} -o ${NAME}

clean		:
				rm -rf ${OBJS}

fclean		:	clean
				rm -rf ${NAME}

debug		:
				${CC} ${CFLAGS} -g ${SRCS} -L./libft -lft -o ${NAME}_debug

run			:	${NAME}
				./${NAME} 5 410 200 200

all			:	${NAME}

re			:	fclean ${NAME}

test_o		:
				${OBJS}

test_s		:
				${SRCS}
