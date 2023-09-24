CC = CC
CFLAG = -Wall -Wextra -Werror
NAME = minishell
SRCS = 

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFALGS) $(OBJS) -o $(NAME)

%.o : %.c
	$(CC) $(CFALGS) -c -o $@ $<

clean:
	rm -f $(OBJS)

fclean:
	rm -f $(OBJS)
	rm -f $(NAME)

re: fclean all

.PHONY: clean fclean all re