#include "minishell.h"

void	exe_data(t_data *data, char **envp, char *root_file_name)
{
	t_arvl	*cur;
	int		flag;
    t_cmd	*cmd;

	cur = data->arvl;
	// if (cur == NULL)//<-메인에서 컨틴뉴 주석하고 테스트 해보기
	// {
	// 	for (int i = 0; data->envp[i]; i++)
	// 	{
	// 		printf("%s\n", data->envp[i]);
	// 	}
	// }
	while (cur != NULL)
	{
		cmd = (t_cmd *)cur->content;
//		if (cur->content->flag)

printf("arvs: %s\n", cmd->args[0]);
		if (ft_strcmp(root_file_name, cmd->args[0]) == 0)//more shell도 그냥 pipex에서 했던 실행에 인자 넣어줘도 될지 체크. 되면 파이프 있는지 체크하고 다른 함수 호출.
			more_shell(data, cmd->args, envp);
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
