#include "minishell.h"

int	cnt_cmd_only(t_arvl *arvl)
{
	int		cnt;
	t_cmd	*cmd;
	t_arvl	*cur;

	cnt = 0;
	cur = arvl;
	while (cur != NULL)
	{
		cmd = (t_cmd *)cur->content;
		if (cmd->flag == SEMICOLON_NONE)
			cnt++;
		cur = cur->next;
	}
	return (cnt);
}

// void	redirect_remake_argv(t_data *data, t_cmd *cmd, int flag)
// {
// 	크게 if문 세개 분기로 나누면 될듯.
// 	만약 out이면 파일 오픈(없으면 만들고 >>이면 append) 하고 dup2로 fd옮겨주기
// 	만약 < 이면 파일 오픈하고(없으면 에러) dup2로 fd옮겨주기
// 	(<<이면 히어독이라 뒤에 인자 리미터로 인식)
// }
// 리다이렉션이 아닌 커맨드의 개수가 하나면서 빌트인 함수면 부모에서 실행.
// 리다이렉션인지 커맨드인지는 플래그로 구분.
// 리다이렉션이면 오는 인자 하나를 파일로 생각.
// < file cat |  wc -w | ls ->     file cat , wc -w, ls 각 노드에 담겨져서 오고 플래그로 구분
// !!아 리다이렉션이 오고 파일이 오면 실행하고 argv의 [1]번째를 커맨드라고 생각할까?
// 위의 예 -> bash-3.2$ < file cat cat cat |  wc | ls
// cat: cat: No such file or directory
// cat: cat: No such file or directory
void	exe_data(t_data *data, char **envp, char *root_file_name)
{
	t_arvl	*cur;
    t_cmd	*cmd;
	int		flag;

	cur = data->arvl;
	// cmd = (t_cmd *)cur->content;
	// if (cmd->flag != SEMICOLON_NONE)
	
	// if (cnt_cmd_only(data->arvl) == 1 && if_buitin_func(data, cmd->args) == 1)
	// {
	// 	execute_one();
	// 	return ;
	// }
	data->cmd_cnt = cnt_cmd_only(data->arvl);
	while (cur != NULL)
	{
		cmd = (t_cmd *)cur->content;
		// 여기 pipex 구조에 맞게 갖다박고 파이프()
		// if (cmd->flag != SEMICOLON_NONE)
		// {
		// 	redirect_remake_argv(data, cmd, cmd->flag);
		// }
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
