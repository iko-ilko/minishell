#include "../minishell.h"

int if_more_shell(t_vars *vars, char **arv, char **temp, char **envp)
{
	if (ft_strcmp(arv[0], temp[0]) != 0)
        return (0);
	// if (temp[1] != NULL)
	// {
	// 	error("minishell: ");
	// 	return (1);
	// }
    int pid = fork();
	if (pid == -1)
		str_error("fork error", "fork");
	else if (pid == 0)
	{
		//리스트->배열 envp를 execve에 넣어줘야함.
		if (execve(arv[0], temp, envp) == -1)
			exit_error("execve error", "execve", 127);
	}
	wait(NULL);
    //!!빌트인 함수도 자식 프로세스에서 실행되게 할거아니면 여기에 waitpid(자식 쉘의 pid) 해야함.
    return (1);
}