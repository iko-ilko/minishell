#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <readline/readline.h>

//ANSI 이스케이프 코드도 사용해야할듯 ... 커서 제대로 찍으려면... 허용된 t 뭐시기 함수들 사용해야할듯...
// 각각 시그널에 맞는 핸들러 함수를 인자로 주거나 IGN, DFL, 주면 될듯?
void    sigint_handler(int signum)
{
    write(1, "\n", 1);
}

void    sigquit_handler(int signum)
{
    exit(0);
}

int main()
{
    char    buf[5];
    char    *line;
    int     pid;
    // do_signal();
    
    signal(SIGINT, sigint_handler  );
    signal(SIGQUIT, sigquit_handler);
    pid = fork();
    {
        if (pid == 0)
        {
            printf("child start\n");
            signal(SIGQUIT, sigquit_handler);
            sleep(10);
            exit(0);
        }
        else if(pid > 0)
            signal(SIGQUIT, SIG_DFL);

    }
    // signal()
    while(1)
    {
        line = readline("minishell> ", buf);
        if (line == NULL)
            exit(0);
        printf("Hello\n");
    }
}