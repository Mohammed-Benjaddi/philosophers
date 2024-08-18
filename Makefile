CC = cc
CFLAGS = -Wall -Wextra -Werror

YELLOW =\033[0;33m
GREEN=\033[0;32m
RED=\033[0;31m
NC=\033[0m

NAME = philo
SRCS = philo.c routine.c initialization.c threads.c utils1.c utils2.c actions.c
OBJS = $(SRCS:.c=.o)

all: $(NAME)

%.o: %.c philo.h
	$(CC) $(CFLAGS) -c -pthread $< -o $@

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
	@echo "$(GREEN)------- philo has been compiled successfully -------$(NC)"

clean:
	rm -rf $(OBJS)
	@echo "$(YELLOW)------- philo's object files have been deleted -------$(NC)"

fclean: clean
	rm -rf $(NAME)
	@echo "$(RED)------- philo has been deleted -------$(NC)"

re: fclean all
