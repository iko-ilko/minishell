#include "../minishell.h"

void	more_shell(t_data *data, char **arvs, char *root_file_name, char **envp)
{

    
    printf("!!!!!%s\n", arvs[0]);//쉘레벨 ++하기 
	if (execve("./minishell", arvs, envp) == -1)
		;//
    //!!빌트인 함수도 자식 프로세스에서 실행되게 할거아니면 여기에 waitpid(자식 쉘의 pid) 해야함.
}