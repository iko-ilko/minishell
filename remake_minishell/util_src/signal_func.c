#include "../minishell.h"

extern int g_exit_code;


//ANSI 이스케이프 코드도 사용해야할듯 ... 커서 제대로 찍으려면... 허용된 t 뭐시기 함수들 사용해야할듯...
// 각각 시그널에 맞는 핸들러 함수를 인자로 주거나 IGN, DFL, 주면 될듯?
//sigterm (ctrl + d) 시그널이 메인에서 들어온 상황에 뭔가 입력받고있으면 처리x. 없으면 미니쉘 꺼지게
//부모 시그인트는 버퍼지우고 개행 .. 부모 시그큍은 무시하게	
//그리고 각 자식 프로세스 들어갈 때 시그널 핸들링 함수 알맞는거 호출해놓으면 될듯?


//child_sigint_handler(int signum)
// {

// }

void aa(int signum)
{
	write(1, "\n", 1);
    rl_on_new_line();
	rl_replace_line("", 0);//readline()함수에 준 문자열 지우기.(엔터 안치고 남아있던 문자열)
	// rl_redisplay();//readline()함수에 준 문자열 출력.
	write(1, "^Caaaaaaaaaaaaaaaaaaaaaaaa", 26);
}
void	set_signal(int flag)
{
	if (flag == PARENT)
	{
		// rl_catch_signals = 0;//^C 출력 무시 <- 얘 있다해서 핸들러 함수가 안되는거 아닌데 ㅗㅇ ㅐ자식 안돼 ㅠㅠ
		signal(SIGINT, parent_sigint_handler);
		signal(SIGQUIT, SIG_IGN);
	}
	else if (HEREDOC)
	{
		signal(SIGINT, parent_sigint_handler);//<---이가 왜 메인으로 빼니까 되냐ㅡㅡ
		signal(SIGQUIT, SIG_DFL);//<-자식 이 핸들링 함수 수정 필
	}
}

void    child_sigint_handler(int signum)//핸들러 함수는 부모,자식으로 나누지말고 함수별로 나누자 main, here_doc, exe
{
    write(1, "\n", 1);
    rl_on_new_line();
	rl_replace_line("", 0);//readline()함수에 준 문자열 지우기.(엔터 안치고 남아있던 문자열)
	g_exit_code = 1;
}////????


void    parent_sigint_handler(int signum)//핸들러 함수는 부모,자식으로 나누지말고 함수별로 나누자 main, here_doc, exe
{
    write(1, "\n", 1);
    rl_on_new_line();
	rl_replace_line("", 0);//readline()함수에 준 문자열 지우기.(엔터 안치고 남아있던 문자열)
	rl_redisplay();//readline()함수에 준 문자열 출력.
	g_exit_code = 1;
}

// void	sigquit_handler(int signum)
// {write(1, "quit\n", 5);
// 	exit(1);
// 	// rl_on_new_line();
// 	// rl_redisplay();
// }