//bash-3.2$ exit 9223372036854775808
// exit
// bash: exit: 9223372036854775808: numeric argument required
// ilko@c10r4s11 ~ % bash

// The default interactive shell is now zsh.
// To update your account to use zsh, please run `chsh -s /bin/zsh`.
// For more details, please visit https://support.apple.com/kb/HT208050.
// bash-3.2$ exit 9223372036854775807
// exit
// 위 예제처럼 long long 범위가 벗어나거나 숫자가 아닌 수 들어오면 numeric ... 에러 띄워야 함.
// exit 명령어 말고도 종료 시그널오면 사용하자.

#include "../minishell.h"

void	exit_func(t_vars *vars, int exit_code)
{
	//릭 정리하고
	exit(exit_code);
}