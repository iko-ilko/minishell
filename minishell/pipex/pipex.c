/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilko <ilko@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 20:12:35 by ilko              #+#    #+#             */
/*   Updated: 2023/09/24 20:50:29 by ilko             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	init_datas(t_datas *data, int arc, char **arv, char **envp)
{
	if (ft_strncmp("here_doc", arv[1], 8) == 0)
	{
		if (ft_strlen(arv[1]) != 8)
			error("here_doc arg error", NULL, 1);
		data->heredoc_f = 1;
	}
	else
		data->heredoc_f = 0;
	data->arv = arv;
	data->envp = envp;
	data->cmd_cnt = arc - 3 - data->heredoc_f;
	data->pipe_cnt = data->cmd_cnt - 1;
	data->all_path = get_all_path(envp);
}

void	set_pipe(t_datas *data, int cmd_idx)
{
	if (cmd_idx > 2)
	{
		close(data->pre_fd[0]);
		close(data->pre_fd[1]);
	}
	data->pre_fd[0] = data->next_fd[0];
	data->pre_fd[1] = data->next_fd[1];
	if (data->pipe_cnt-- && pipe(data->next_fd) == -1)
		error("pipe error", "", 1);
}

void	execute_child(t_datas *data, char **arv, char *infile, char *outfile)
{
	int	cmd_idx;

	cmd_idx = 0;
	while (++cmd_idx <= data->cmd_cnt)
	{
		set_pipe(data, cmd_idx);
		data->cur_cmd_arvs = ft_split(arv[cmd_idx + 1 + data->heredoc_f], ' ');
		data->cur_pid = fork();
		if (data->cur_pid == -1)
			error("fork error", "", 1);
		else if (data->cur_pid == 0)
		{
			if (cmd_idx == 1)
				first_child(data, infile);
			else if (cmd_idx == data->cmd_cnt)
				last_child(data, outfile);
			else
				multiple_child(data);
		}
		free_multi(data->cur_cmd_arvs);
	}
	free_multi(data->all_path);
	exit_parent(data->cur_pid, data->next_fd);
}

void	here_doc(char **arv)
{
	int		here_doc_temp;
	char	*line;

	here_doc_temp = open("here_doc.temp", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (here_doc_temp == -1)
		error("open error", NULL, 1);
	while (1)
	{
		write(1, "pipe heredoc> ", 14);
		line = get_next_line(0);
		if (!line)
			error("get_next_line error", NULL, 1);
		if (!ft_strncmp(arv[2], line, ft_strlen(arv[2])))
			break ;
		write(here_doc_temp, line, ft_strlen(line));
		free(line);
	}
	free(line);
	close(here_doc_temp);
}

int	main(int arc, char **arv, char **envp)
{
	t_datas	data;

	init_datas(&data, arc, arv, envp);
	if (data.heredoc_f == 1)
	{
		here_doc(arv);
		execute_child(&data, arv, "here_doc.temp", arv[arc - 1]);
	}
	else
		execute_child(&data, arv, arv[1], arv[arc - 1]);
}
