#include "../minishell.h"
//pid을 구조체로 넣으면서 str_error()만들어야 함
//error를 호출하는 자식이든 부모는 뭔갈 실행 했을 때니 구조체 던져쥬자그냥.
//일단 에러 함수는 나중에 넣는걸로 ..
//프로그램이 정상 종료 하거나 예측 가능한 에러가 떴지만 종종료료를  시키지 않은 경우는 free를 명시적으로 핸들링 해줘서 런타임에 누수는 없애고,
//malloc을 실패 한 경우는 메모리자체에 문제가 있을 수 있어서 종료를 할 테니 exit를 해버린다.(결국 exit로 논란이 있는 이유는 자원 회수의 관점보다는 자원 관리의 관점으로 접근하니까) 
void	exit_error(char *message, char *reason, int exit_code)
{
	write(2, "minishell: ", 12);
	if (reason != NULL)
	{
		write(2, reason, ft_strlen(reason));
		write(2, ": ", 2);
	}
	write(2, message, ft_strlen(message));
	write(2, "\n", 1);
	//시그널 들어오면 좀 다르게 처리될듯?
	exit(exit_code);
}

void	str_error(char *message, char *reason)
{
	write(2, "minishell: ", 12);
	if (reason != NULL)
	{
		write(2, reason, ft_strlen(reason));
		write(2, ": ", 2);
	}
	write(2, message, ft_strlen(message));
	write(2, "\n", 1);
}

void	my_perror(char *infile_name)
{
	perror("minishell: ");
	// exi
}
