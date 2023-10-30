#include "../minishell.h"

void	redirect_file_out(t_data *data, t_pipe *pipe_data, t_cmd *cmd)
{
	int	fd;

	if (cmd->flag == SIN_REDI_R)
		fd = open(cmd->args[0], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else
		fd = open(cmd->args[0], O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
	{
		my_perror(cmd->args[0]);
		return ;
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
}
void	redirect_file_in(t_data *data, t_pipe *pipe_data, t_cmd *cmd)
{
	int fd;

	if (cmd->flag == SIN_REDI_L)
	{
		fd = open(cmd->args[0], O_RDONLY);
		if (fd == -1)
		{
			my_perror(cmd->args[0]);
			return ;
		}
		dup2(fd, STDIN_FILENO);
		close(fd);
	}
	else
	{
		here_doc(cmd->args[0]);
		pipe_data->heredoc_f = 1;
	}
}