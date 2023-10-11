#include "../minishell.h"

void	more_shell(t_data *data, char **arvs, char **envp)
{
	if (arvs[1] != NULL)
	{
		//커맨드일 경우 에러
		//파일or디렉일 경우 에러
		return ;
	}
		
    int pid = fork();
	if (pid == -1)
		str_error("fork error", "fork");
	else if (pid == 0)
	{
		//리스트->배열 envp를 execve에 넣어줘야함.
		if (execve(arvs[0], arvs, envp) == -1)
			exit_error("execve error", "execve", 127);
	}
	wait(NULL);
    //!!빌트인 함수도 자식 프로세스에서 실행되게 할거아니면 여기에 waitpid(자식 쉘의 pid) 해야함.
}