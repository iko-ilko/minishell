#include "../minishell.h"

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

void	set_pipe(t_pipe *pip)
{
	(pip->cmd_idx)++;
	if (pip->cmd_idx > 2)
	{
		close(pip->pre_fd[0]);
		close(pip->pre_fd[1]);
	}
	pip->pre_fd[0] = pip->next_fd[0];
	pip->pre_fd[1] = pip->next_fd[1];
	if (pip->pipe_cnt - pip->cmd_idx >= 0 && pipe(pip->next_fd) == -1)//첫번째조건 체크해봐야함.
		perror("minishell: ");
}

int	cnt_pipe(t_arvl *arvl)
{
	int		cnt;
	t_cmd	*cmd;
	t_arvl	*cur;

	cnt = 0;
	cur = arvl;
	while (cur != NULL)
	{
		cmd = (t_cmd *)cur->content;
		if (cmd->flag == PIPE)
			cnt++;
		cur = cur->next;
	}
	return (cnt);
}

void	wait_parent(t_data *data, int fd[2])
{
	int status;

	close(fd[0]);
	close(fd[1]);
	waitpid(data->cur_pid, &status, 0);
	while (wait(NULL) != -1)
		;
	data->last_exit_code = WEXITSTATUS(status);
}
