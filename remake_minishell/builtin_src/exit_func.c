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

//arvs[1]의 엑싯코드로 종료.
//만약 arvs[2] (즉, 두번째 인자)가 있다면 에러 메세지 출력하고 종료.
//만약 arvs[1]이 범위가 벗어나거나 숫자가 아니면 에러 메세지 출력하고 종료.
void	exit_exe(t_data *data, char **arvs)
{
	int		exit_code = 0;//임시

	write(1, "exit\n", 5);
	free_vars(data);
	//릭 정리하고
	//check_arv_number() 는 숫자인지 체크하고 long long 범위 안넘는지 체크
	// if (check_arv_number(arvs) == -1)
	// 	return ;
	exit(exit_code);
}

