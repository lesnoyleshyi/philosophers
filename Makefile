
NAME	=	philo

B_NAME	=	philo_bonus

HEADER	=	philo.h

B_HEADER =	philo_bonus.h

SRC_F	=	philo.c	get_arguments_funcs.c	philo_utils.c \
			simulation_funcs.c	watch_funcs.c

B_SRC_F	=	philo_bonus.c	get_arguments_funcs_bonus.c	philo_utils_bonus.c \
			simulation_funcs_bonus.c	watch_funcs_bonus.c

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
				make all NAME=${B_NAME} OBJS="${B_OBJS}" \
 										SRC_DIR=${B_SRC_DIR} HEADER=${B_HEADER}

clean		:
				rm -rf ${OBJS} ${B_OBJS}

fclean		:	clean
				rm -rf ${NAME} ${B_NAME}

debug		:
				${CC} ${CFLAGS} -g ${SRCS} -L./libft -lft -o ${NAME}_debug

run			:	${NAME}
				./${NAME} 4 410 200 200

all			:	${NAME}

re			:	fclean ${NAME}

ch_leaks_b	:
				leaks -atExit -- ./philo_bonus 4 410 200 200 2
