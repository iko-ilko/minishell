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

extern int g_exit_code;


//arvs[1]의 엑싯코드로 종료.
//만약 arvs[2] (즉, 두번째 인자)가 있다면 에러 메세지 출력하고 종료.
//만약 arvs[1]이 범위가 벗어나거나 숫자가 아니면 에러 메세지 출력하고 종료.
void	exit_exe(t_data *data, char **arvs)
{
	int		exit_code = 0;//임시

	write(data->cur_pipe->in_out_fd[1], "exit\n", 5);
	// free_last(data);

	// if arvs[1]이 숫자면 g_exit_code에 저장.하고, <- 음수면 unsigned int 범위를 넘어가서 언더 플로우일으켜서 양수값으로 변경
	// long long 범위를 넘어가거나(push_swap에서 쓴 아토이 쓰기) 숫자가 아니면 에러 메세지 출력하고 종료.<- exit code는 255가 됨.
	// else if arvs[2]가 있다면 exit_code는 1이 되고, 에러 메세지 출력하고 return. <- if else if 는 우분투에서 테스트 한 결과(arvs[1]이 우선)

	exit(0);
}
