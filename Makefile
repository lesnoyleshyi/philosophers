
NAME	=	philo

B_NAME	=	philo_bonus

HEADER	=	philo.h

B_HEADER =	philo_bonus.h

SRC_F	=	philo.c	get_arguments_funcs.c	simulation_funcs.c	philo_utils.c \
			watch_funcs.c

B_SRC_F	=	philo_bonus.c

SRC_DIR	=	./srcs

B_SRC_DIR =	./srcs_bonus

SRCS	=	$(addprefix ${SRC_DIR}/,${SRC_F})

B_SRCS	=	$(addprefix ${B_SRC_DIR}/,${B_SRC_F})

OBJS	=	${SRCS:.c=.o}

B_OBJS	=	${B_SRCS:.c=.o}

CC		=	cc

CFLAGS	=	-Wall -Werror -Wextra

%.o			:	%.c ${SRC_DIR}/${HEADER}
				${CC} ${CFLAGS} $< -c -o $@

.PHONY		:	all re clean fclean debug run

${NAME}		:	${OBJS}
				${CC} ${CFLAGS} ${OBJS} -o ${NAME}

bonus		:
				make all NAME=${B_NAME} OBJS=${B_OBJS}

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
