#include "../minishell.h"
//pid을 구조체로 넣으면서 str_error()만들어야 함
//error를 호출하는 자식이든 부모는 뭔갈 실행 했을 때니 구조체 던져쥬자그냥.
void	error(char *message, char *reason, int exit_code)
{
	write(2, "minishell: ", 12);
	write(2, reason, ft_strlen(reason));
	write(2, ": ", 2);
	write(2, message, ft_strlen(message));
	write(2, "\n", 1);
	printf("pid:%d\n", g_pid);
	if (g_pid == 0)
		exit(exit_code);
}