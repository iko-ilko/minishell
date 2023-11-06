CC = cc -Wall -Wextra -Werror
SRCS = pipex.c error_done.c execute_child.c str_func2.c str_func.c get_next_line.c
NAME = pipex
OBJS = $(SRCS:.c=.o)


all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(OBJS) -o $(NAME)

%.o:%.c
	$(CC) -c $< -o $@

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(NAME)

re: fclean all