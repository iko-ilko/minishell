#include "minishell.h"

void	exe_data(t_data *data, char **envp, char *root_file_name)
{
	t_arvl	*cur;
	char	**temp_argv;
	int		flag;
    t_cmd	*cmd;

	cur = data->arvl;
	while (cur != NULL)
	{
		cmd = (t_cmd *)cur->content;
//		if (cur->content->flag)
printf("arvs: %s\n", cmd->args[0]);
		if (ft_strcmp(root_file_name, cmd->args[0]) == 0)
			more_shell(data, cmd->args, root_file_name, envp);
		else if (if_buitin_func(data, cmd->args) == 1)
			;
		//else
		//	execute_argv(data, cmd->content);






		// if (if_more_shell(data, cmd->args, cmd->args, envp) == 1)
		// 	;
		// else if (if_buitin_func(data, cmd->args) == 1)
		// 	;
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
