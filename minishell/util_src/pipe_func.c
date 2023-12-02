/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_func.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilko <ilko@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 15:40:23 by ilko              #+#    #+#             */
/*   Updated: 2023/12/02 21:06:46 by ilko             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	set_pipe(t_pipe *pip)
{
	(pip->cmd_idx)++;
	if (pip->cmd_idx > 1)
	{
		close(pip->pre_fd[0]);
		close(pip->pre_fd[1]);
	}
	pip->pre_fd[0] = pip->next_fd[0];
	pip->pre_fd[1] = pip->next_fd[1];
	pip->in_out_fd[0] = 0;
	pip->in_out_fd[1] = 1;
	pip->pipe_fail_flag = pipe(pip->next_fd);
	if (pip->pipe_cnt - pip->cmd_idx > 0 && pip->pipe_fail_flag == -1)
		perror("minishell: ");
}

int	cnt_pipe(t_cmd_node *cmd)
{
	int	cnt;

	cnt = 0;
	while (cmd != NULL)
	{
		cnt++;
		cmd = cmd->next;
	}
	if (cnt > 0)
		cnt--;
	return (cnt);
}

int	next_if_pipe_fail(t_pipe *pipe_data, t_cmd_node **cur)
{
	if (pipe_data->pipe_fail_flag == -1)
	{
		pipe_data->pipe_fail_flag = 0;
		*cur = (*cur)->next;
		return (-1);
	}
	return (0);
}

void	set_pipe_child(t_pipe *pipe_data)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if (pipe_data->cmd_idx != 0)
		dup2(pipe_data->pre_fd[0], 0);
	if (pipe_data->cmd_idx != pipe_data->pipe_cnt)
		dup2(pipe_data->next_fd[1], 1);
	if (pipe_data->in_out_fd[0] != 0)
		dup2(pipe_data->in_out_fd[0], 0);
	if (pipe_data->in_out_fd[1] != 1)
		dup2(pipe_data->in_out_fd[1], 1);
}
