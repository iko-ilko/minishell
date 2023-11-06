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
// 	지금 생각하고있는 구조는 여기서 파이프 만들고 초기화 해주는게 맞을듯. 각 파이프와 널 까지 노드들에서만 해당되는 리다이렉션 fd 값일테니까..
// 그럼 pre, next를 음 ....redi구조체에서 받아온 fd값..을 뭘로 초기화? 아니 애초에 이 시점에 dup2로 건들여주는게 맞나?
// 일단 파싱에서의 리다이렉션 함수 만들고 생각해보자 ..
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
	else if (pip->pipe_cnt - pip->cmd_idx >= 0)
	{
		dup2(pip->next_fd[0], 0);
		dup2(pip->next_fd[1], 1);
	}
	//여기서 파이프 만들면 fd 1, 0로 초기화 해줘야하나?
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
	printf("cnt: %d\n", cnt);
	return (cnt);
}

void	wait_parent(t_data *data, int fd[2])
{
	int status;

	close(fd[0]);
	close(fd[1]);
	printf("last: %d\n", data->last_exit_code);
	waitpid(data->cur_pid, &status, 0);
	while (wait(NULL) != -1)
		;
	data->last_exit_code = WEXITSTATUS(status);
}
