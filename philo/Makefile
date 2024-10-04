SRCFILES = ./actions.c ./atoi.c  ./listener.c  ./utils.c ./main.c ./parsing.c

CC = cc  -Wall -Wextra -Werror

OBJECTFILES = $(SRCFILES:.c=.o)

NAME = ./philo

all: $(NAME)

$(NAME): $(OBJECTFILES)
	$(CC) $(OBJECTFILES) -o $@

%.o: %.c ./philo.h
	$(CC) -c $< -o $@

clean:
	rm -f $(OBJECTFILES)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: clean