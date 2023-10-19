CC = cc #-Wall -Wextra -Werror
SRCS = minishell.c parsing.c execute.c \
	./builtin_src/builtin_main.c \
    ./builtin_src/cd_func.c \
    ./builtin_src/echo_func.c \
    ./builtin_src/env_func.c \
    ./builtin_src/exit_func.c \
    ./builtin_src/export_func.c \
    ./builtin_src/pwd_func.c \
    ./builtin_src/unset_func.c \
	\
	./child_process_src/shell_child.c \
	./child_process_src/execute_child.c \
	\
	./util_src/list_func.c \
	./util_src/signal_func.c \
	./util_src/init_func.c \
	./util_src/free_func.c \
	\
	./str_src/str_func1.c \
	./str_src/str_func2.c \
	./str_src/str_func3.c \
	./str_src/str_func4.c \
	\
	./error_done_src/error.c
NAME = minishell
OBJS = $(SRCS:.c=.o)


all: $(NAME)
	

$(NAME): $(OBJS)
#	$(CC) -fsanitize=address $(OBJS) -lreadline -o $(NAME)
	$(CC) -g3 $(OBJS) -lreadline -o $(NAME)

%.o:%.c
#	$(CC) -fsanitize=address -c $< -o $@
	$(CC) -g3 -c $< -o $@


clean:
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(NAME)
re: fclean all
###############temp
and: all clean
#####################