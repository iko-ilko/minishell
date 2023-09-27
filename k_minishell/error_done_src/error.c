#include "../minishell.h"

void	error(char *message, char *reason, int exit_code)
{
	write(2, "pipex: ", 7);
	write(2, reason, ft_strlen(reason));
	write(2, ": ", 2);
	write(2, message, ft_strlen(message));
	write(2, "\n", 1);
	exit(exit_code);
}