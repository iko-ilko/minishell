/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilko <ilko@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 15:40:34 by ilko              #+#    #+#             */
/*   Updated: 2023/12/01 16:07:04 by ilko             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	redirect_file(char **envp, t_redi *redi, t_pipe *pipe_data)
{
	while (redi != NULL)
	{
		if (redi->flag == SIN_REDI_R || redi->flag == DOUB_REDI_R)
		{
			if (pipe_data->in_out_fd[1] != 1)
				close(pipe_data->in_out_fd[1]);
			pipe_data->in_out_fd[1] = redirect_file_out(redi->flag, \
			redi->file_n);
		}
		else
		{
			if (pipe_data->in_out_fd[0] != 0)
				close(pipe_data->in_out_fd[0]);
			pipe_data->in_out_fd[0] = redirect_file_in(envp, redi->flag, \
			redi->file_n, &pipe_data->heredoc_f);
		}
		redi = redi->next;
	}
}

int	redirect_file_out(int flag, char *file_n)
{
	int	fd;

	if (flag == SIN_REDI_R)
		fd = open(file_n, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else
		fd = open(file_n, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
		return (redi_perror(file_n));
	return (fd);
}

int	redirect_file_in(char **envp, int flag, char *file_n, int *heredoc_f)
{
	int	fd;

	if (flag == SIN_REDI_L)
	{
		fd = open(file_n, O_RDONLY);
		if (fd == -1)
			return (redi_perror(file_n));
	}
	else
	{
		fd = open("here_doc.temp", O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd == -1)
			return (redi_perror("here_doc.temp"));
		here_doc(envp, file_n, fd);
		*heredoc_f = 1;
		close(fd);
		fd = open("here_doc.temp", O_RDONLY);
		if (fd == -1)
			return (redi_perror("here_doc.temp"));
	}
	return (fd);
}
