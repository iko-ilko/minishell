#include "minishell.h"

int main(int arc, char **arv, char **env)
{
	t_vars	vars;
    char    buf[5];
    char    *line;
	int i = 0;

	// while (env[i])
	// {
	// 	printf("%s\n", env[i]);
	// 	i++;
	// }
	// exit(1);
    // do_signal();
    
            // int k = 0;
            // while (envp[k])
            // {
            //     printf("%s\n", envp[k]);
            //     k++;
            // }
	
	init_exe_data(&vars, env, arv[0]);
    signal(SIGINT, sigint_handler);
    signal(SIGQUIT, SIG_IGN);
    // pid = fork();
    // {
    //     if (pid == 0)
    //     {
    //         printf("child start\n");
    //         signal(SIGQUIT, sigquit_handler);
    //         sleep(10);
    //         exit(0);
    //     }
    //     else if(pid > 0)
    //         signal(SIGQUIT, SIG_DFL);

    // }
    // signal()
	// 빌트인 커맨드 단독 일 때만 부모 프로세스에서 빌트인 실행
    while(1)
    {
        line = readline("minishell$ ");
		if (line == NULL)
			break;
		char **temp = ft_split(line, ' ');
		if (temp[0] == NULL)
			continue;
	    add_history(line);
		free(line);
        //save_history(&vars, temp[0]);
        //save_history(line); <- 이 안에 add_history() 넣자.
        //a.out 명시하지않고 arv[0] 과 temp[0] 비교해도 될듯?
        if (if_more_shell(&vars, arv, temp, env) == 1)
            continue ;
		if (if_buitin_func(&vars, temp) == 1)
			continue ;
		//빌트인 다음 커맨드 실행
		if (ft_strcmp(temp[0], "ls") == 0)
		{
			int pid = fork();
			if (pid == 0)
				execve("/bin/ls", temp, env);
		}
		free_double(&temp);
		// int i = 0;
		// while (temp[i])
		// 	free(temp[i++]);
		// free(temp);
    }
}
//함수 잘 빼자 .. if_more_shell() -> shell_child.c , save_history()