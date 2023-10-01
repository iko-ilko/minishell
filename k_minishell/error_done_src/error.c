#include "../minishell.h"
//pid을 구조체로 넣으면서 str_error()만들어야 함
//error를 호출하는 자식이든 부모는 뭔갈 실행 했을 때니 구조체 던져쥬자그냥.
//일단 에러 함수는 나중에 넣는걸로 ..
void	error(char *message, char *reason, int exit_code)
{
	write(2, "minishell: ", 12);
	if (reason != NULL)
	{
		write(2, reason, ft_strlen(reason));
		write(2, ": ", 2);
	}
	write(2, message, ft_strlen(message));
	write(2, "\n", 1);
	// if 부모면 return, 자식이면 exit(exit_code) -> 구조체 or 플래그로 구분
		//exit(exit_code);
}