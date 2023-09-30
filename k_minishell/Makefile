CC = cc #-Wall -Wextra -Werror
SRCS = signal_func.c init_func.c \
    ./builtin_src/cd_func.c \
    ./builtin_src/echo_func.c \
    ./builtin_src/env_func.c \
    ./builtin_src/exit_func.c \
    ./builtin_src/export_func.c \
    ./builtin_src/pwd_func.c \
    ./builtin_src/unset_func.c \
	\
	./util_src/list_func.c \
	\
	./str_src/str_func1.c \
	./str_src/str_func2.c \
	./str_src/str_func3.c \
	\
	./error_done_src/error.c
NAME = a.out #minishell_test
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