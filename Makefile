CC = cc
CFLAGS = #-fsanitize=address -g #-Wall -Wextra -Werror

NAME = philo
SRCS = philo.c utils.c routine.c initialization.c threads.c
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
