#include "minishell.h"

//ANSI 이스케이프 코드도 사용해야할듯 ... 커서 제대로 찍으려면... 허용된 t 뭐시기 함수들 사용해야할듯...
// 각각 시그널에 맞는 핸들러 함수를 인자로 주거나 IGN, DFL, 주면 될듯?
//sigterm (ctrl + d) 시그널이 메인에서 들어온 상황에 뭔가 입력받고있으면 처리x. 없으면 미니쉘 꺼지게
//부모 시그인트는 버퍼지우고 개행 .. 부모 시그큍은 무시하게	
//그리고 각 자식 프로세스 들어갈 때 시그널 핸들링 함수 알맞는거 호출해놓으면 될듯?

void    sigint_handler(int signum)//핸들러 함수는 부모,자식으로 나누지말고 함수별로 나누자 main, here_doc, exe
{
    write(1, "\n", 1);
    rl_on_new_line();
	rl_replace_line("", 0);//readline()함수에 준 문자열 지우기.(엔터 안치고 남아있던 문자열)
	rl_redisplay();//readline()함수에 준 문자열 출력.
}

void    sigquit_handler(int signum)
{
    exit(0);
}

int main(int arc, char **arv, char **envp)
{
	t_vars	vars;
    char    buf[5];
    char    *line;
	int i = 0;

	// while (envp[i])
	// {
	// 	printf("%s\n", envp[i]);
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
	
	init_exe_data(&vars, envp);
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
    while(1)
    {
        line = readline("minishell$ ");
		if (line == NULL)
			break;
		char **temp = ft_split(line, ' ');
		free(line);
		if (temp[0] == NULL)
			continue;
        save_history(&vars, temp[0]);
        //save_history(line); <- 이 안에 add_history() 넣자.
        //a.out 명시하지않고 arv[0] 과 temp[0] 비교해도 될듯?
        if (if_more_shell(&vars, arv, temp, envp) == 1)
            continue ;
		if (if_buitin_func(&vars, temp) == 1)
			continue ;
		//빌트인 다음 커맨드 실행
		if (ft_strcmp(temp[0], "ls") == 0)
		{
			int pid = fork();
			if (pid == 0)
				execve("/bin/ls", temp, envp);
		}
		int i = 0;
		while (temp[i])
			free(temp[i++]);
		free(temp);
    }
}
//함수 잘 빼자 .. if_more_shell() -> shell_child.c , save_history()