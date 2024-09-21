SRCS = ./philos/actions.c ./philos/atoi.c  ./philos/listener.c  ./philos/utils.c ./philos/main.c 

OBJ = ${SRCS:.c=.o}

NAME = philo

CC = cc #-fsanitize=address -g
RM = rm -rf
CFLAGS =# -Wall -Wextra -Werror

%.o: %.c ./Includes/philo.h
	${CC} ${CFLAGS} -c $< -o $@

${NAME}: ${OBJ}
	${CC} ${OBJ} -o ${NAME}

all: ${NAME}

clean:
	${RM} ${OBJ}

fclean: clean
	${RM} ${NAME} ${NAME_BONUS}

re: fclean all

.PHONY: clean