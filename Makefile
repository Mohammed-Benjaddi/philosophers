CC = cc
CFLAGS = -Wall -Wextra -Werror #-g -fsanitize=thread

NAME = philo
SRCS = philo.c routine.c initialization.c threads.c utils1.c utils2.c actions.c
OBJS = $(SRCS:.c=.o)

all: $(NAME)

%.o: %.c philo.h
	$(CC) $(CFLAGS) -c -pthread $< -o $@

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(NAME)

re: fclean all
