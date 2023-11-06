/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_child.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilko <ilko@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 20:10:33 by ilko              #+#    #+#             */
/*   Updated: 2023/09/24 20:14:35 by ilko             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	**get_all_path(char **envp)
{
	int		i;

	i = -1;
	while (envp[++i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
		{
			return (ft_split(envp[i] + 5, ':'));
		}
	}
	return (0);
}

char	*find_command(char *cmd, char **all_path)
{
	int		i;
	char	*temp;
	char	*result;

	if (cmd[0] == '/' && access(cmd, X_OK) == 0)
		return (ft_strdup(cmd));
	i = -1;
	while (all_path[++i])
	{
		result = ft_strjoin(all_path[i], "/");
		temp = result;
		result = ft_strjoin(result, cmd);
		free(temp);
		if (access(result, X_OK) == 0)
			return (result);
		free(result);
	}
	return (NULL);
}

void	first_child(t_datas *data, char *infile_name)
{
	int		infile_fd;
	char	*cmd;
	char	*error_reason;

	infile_fd = open(infile_name, O_RDONLY);
	if (infile_fd == -1)
	{
		error_reason = ft_strjoin("pipex: ", infile_name);
		perror(error_reason);
		free(error_reason);
		exit(1);
	}
	cmd = data->cur_cmd_arvs[0];
	data->cur_cmd_path = find_command(cmd, data->all_path);
	dup2(infile_fd, 0);
	dup2(data->next_fd[1], 1);
	close(data->next_fd[0]);
	close(data->next_fd[1]);
	close(infile_fd);
	if (data->heredoc_f == 1)
		unlink("here_doc.temp");
	if (execve(data->cur_cmd_path, data->cur_cmd_arvs, data->envp) == -1)
		error("command not found", cmd, 127);
}

void	multiple_child(t_datas *data)
{
	char	*cmd;

	cmd = data->cur_cmd_arvs[0];
	data->cur_cmd_path = find_command(cmd, data->all_path);
	dup2(data->pre_fd[0], 0);
	dup2(data->next_fd[1], 1);
	close(data->next_fd[0]);
	close(data->next_fd[1]);
	close(data->pre_fd[1]);
	close(data->pre_fd[0]);
	if (execve(data->cur_cmd_path, data->cur_cmd_arvs, data->envp) == -1)
		error("command not found", cmd, 127);
}

void	last_child(t_datas *data, char *outfile_name)
{
	int		outfile_fd;
	char	*cmd;

	if (data->heredoc_f == 1)
		outfile_fd = open(outfile_name, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		outfile_fd = open(outfile_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (outfile_fd == -1)
		error("open error", NULL, 1);
	cmd = data->cur_cmd_arvs[0];
	data->cur_cmd_path = find_command(cmd, data->all_path);
	dup2(data->next_fd[0], 0);
	dup2(outfile_fd, 1);
	close(data->next_fd[0]);
	close(data->next_fd[1]);
	close(outfile_fd);
	if (execve(data->cur_cmd_path, data->cur_cmd_arvs, data->envp) == -1)
		error("command not found", cmd, 127);
}
