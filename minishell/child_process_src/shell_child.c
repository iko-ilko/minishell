#include "../minishell.h"

int if_more_shell(t_vars *vars, char **arv, char **temp, char **envp)
{
	if (ft_strcmp(arv[0], temp[0]) != 0)
        return (0);

    
    printf("!!!!!%s\n", arv[0]);//쉘레벨 ++하기 
		execve("./minishell", temp, envp);
    //!!빌트인 함수도 자식 프로세스에서 실행되게 할거아니면 여기에 waitpid(자식 쉘의 pid) 해야함.
    return (1);
}