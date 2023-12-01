CC = cc #-Wall -Wextra -Werror
SRCS = minishell.c \
	./execute_src/execute.c \
	\
	./builtin_src/builtin_main.c \
    ./builtin_src/cd_func.c \
    ./builtin_src/echo_func.c \
    ./builtin_src/env_func.c \
    ./builtin_src/exit_func.c \
    ./builtin_src/export_func.c \
    ./builtin_src/pwd_func.c \
    ./builtin_src/unset_func.c \
	\
	./util_src/pipe_func.c \
	./util_src/redirection.c \
	./util_src/here_doc.c \
	./util_src/list_func.c \
	./util_src/list_func2.c \
	./util_src/signal_func.c \
	./util_src/init_func.c \
	./util_src/free_func.c \
	./util_src/remake_func.c \
	./util_src/path_func.c \
	\
	./str_src/str_func1.c \
	./str_src/str_func2.c \
	./str_src/str_func3.c \
	./str_src/str_func4.c \
	./str_src/str_func5.c \
	\
	./parsing_src/parsing_first.c \
	./parsing_src/parsing_init.c \
	./parsing_src/parsing_init_utils.c \
	./parsing_src/parsing_second_utils.c \
	./parsing_src/parsing_second.c \
	./parsing_src/parsing_set.c \
	./parsing_src/word_parsing.c \
	./parsing_src/word_parsing_utils.c \
	\
	./error_done_src/error.c
NAME = minishell
OBJS = $(SRCS:.c=.o)


all: $(NAME)
	

$(NAME): $(OBJS)
	$(CC) -g3 -fsanitize=address $(OBJS) -lreadline -o $(NAME)
#	$(CC) -g3 $(OBJS) -lreadline -o $(NAME)

%.o:%.c
	$(CC) -g3 -fsanitize=address -c $< -o $@
#	$(CC) -g3 -c $< -o $@

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(NAME)
re: fclean all
###############temp
and: all clean
#####################