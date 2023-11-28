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
	int	suc_flag;
	int	exit_code;

	if (data->cur_pipe->pipe_cnt == 0)
		write(2, "exit\n", 5);
	suc_flag = 0;
	exit_code = ft_atous_minishell(arvs[1], &suc_flag);
	if (arvs[1] != NULL && suc_flag == FAIL)
	{
		write(2, "minishell: exit: ", 17);
		write(2, arvs[1], ft_strlen(arvs[1]));
		write(2, ": numeric argument required\n", 28);
	}
	else if (arvs[1] != NULL && arvs[2] != NULL)
	{
		g_exit_code = 1;
		write(2, "minishell: exit: too many arguments\n", 36);
		return ;
	}
	free_double(&data->envp);
	exit(exit_code);
	g_exit_code = exit_code;
}
