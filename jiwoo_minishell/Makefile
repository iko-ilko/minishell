CC = cc #-Wall -Wextra -Werror
SRCS = libft_utils_two.c libft_utils.c main.c
NAME = minishell
OBJS = $(SRCS:.c=.o)


all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(OBJS) -lreadline -o $(NAME)

%.o:%.c
	$(CC) -c $< -o $@

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(NAME)

re: fclean all