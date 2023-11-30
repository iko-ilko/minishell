#include "../minishell.h"

extern int g_exit_code;

void	echo_exe(t_data *data, char **arvs)
{
	int	n_flag;
	int	i;

	n_flag = 0;
	if (arvs[1] != NULL && ft_strcmp(arvs[1], "-n") == 0)
		n_flag = 1;
	i = n_flag + 1;
	while (arvs[i] != NULL)
	{
		write(data->cur_pipe->in_out_fd[1], arvs[i], ft_strlen(arvs[i]));
		write(data->cur_pipe->in_out_fd[1], " ", 1);
		i++;
	}
	if (n_flag == 0)
		write(data->cur_pipe->in_out_fd[1], "\n", 1);
}
