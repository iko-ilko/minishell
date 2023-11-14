#include "../minishell.h"

void	redirect_file(t_redi *redi, t_pipe *pipe_data)
{
	while (redi != NULL)
	{
		if (redi->flag == SIN_REDI_R || redi->flag == DOUB_REDI_R)
			// pipe_data->in_out_fd[1] = redirect_file_out(redi->flag, redi->file_name);
			dup2(redirect_file_out(redi->flag, redi->file_name), pipe_data->in_out_fd[1]);
		else
			// pipe_data->in_out_fd[0] = redirect_file_in(redi->flag, redi->file_name, &pipe_data->heredoc_f);
			dup2(redirect_file_in(redi->flag, redi->file_name, &pipe_data->heredoc_f), pipe_data->in_out_fd[0]);
		redi = redi->next;
	}
	// dup2(pipe_data->in_out_fd[0], 0);//부모와 자식 입장에서 잘 생각해보고 구조에 맞게 리다이렉션 처리. << limiter 문제 있음
	// dup2(pipe_data->in_out_fd[1], 1);
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
	printf("in parent out fd:%d\n", fd);
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
