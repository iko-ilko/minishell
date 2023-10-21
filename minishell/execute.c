#include "minishell.h"

void	exe_data(t_data *data, char **envp, char *root_file_name)
{
	t_arvl	*cur;
	int		flag;
    t_cmd	*cmd;

	cur = data->arvl;
	if (cur && cur->next != NULL)
	{
		execute_one();
		return ;
	}
	while (cur != NULL)
	{
		// 여기 pipex 구조에 맞게 갖다박고 파이프()
		if (ft_strcmp(root_file_name, cmd->args[0]) == 0)//more shell도 그냥 pipex에서 했던 실행에 인자 넣어줘도 될지 체크. 되면 파이프 있는지 체크하고 다른 함수 호출.
			more_shell(data, cmd->args, envp);
		else if (if_buitin_func(data, cmd->args) == 1)
			;
		//else
		//	execute_argv(data, cmd->content);
		cur = cur->next;
	}
	/*
	//빌트인 다음 커맨드 실행
	if (ft_strcmp(temp[0], "ls") == 0)
	{
		int pid = fork();
		if (pid == 0)
			execve("/bin/ls", temp, envp);
	}*/
}

			//execve("./minishell", arvl->content->args, /*ㄹㅣ스트 다시 2차원 포인터 바꾼 것것*/);
