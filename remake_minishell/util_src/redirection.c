#include "../minishell.h"

void	redirect_file(t_redi *redi, t_pipe *pipe_data)
{
	while (redi != NULL)
	{
		if (redi->flag == SIN_REDI_R || redi->flag == DOUB_REDI_R)
			pipe_data->in_out_fd[1] = redirect_file_out(redi->flag, redi->file_name);
		else
			pipe_data->in_out_fd[0] = redirect_file_in(redi->flag, redi->file_name, &pipe_data->heredoc_f);
		redi = redi->next;
	}

}


int	redirect_file_out(int flag, char *file_name)
{
	int	fd;

	if (flag == SIN_REDI_R)
		fd = open(file_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else
		fd = open(file_name, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
	{
		my_perror(file_name);
		return (-1);
	}
	return (fd);
}
int	redirect_file_in(int flag, char *file_name, int *heredoc_f)
{
	int	fd;

	if (flag == SIN_REDI_L)
	{
		fd = open(file_name, O_RDONLY);
		if (fd == -1)
		{
			my_perror(file_name);
			return (-1);
		}
	}
	else
	{
		fd = open("here_doc.temp", O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd == -1)
		{
			my_perror("here_doc.temp");
			return (-1);
		}
		here_doc(file_name, fd);
		*heredoc_f = 1;
	}
	return (fd);
}
