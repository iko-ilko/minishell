//pwd 뒤에 인자가 몇 개있든 신경 안씀.
// ?? unset PWD 해도 $PWD 값이 있네?
// $PWD, ~ 는 파싱에서 주어진 getcwd(), getenv("HOME") <- 시스템 환경변수에서 들고오는듯.

#include "../minishell.h"

extern int g_exit_code;

void	pwd_exe(t_data *data, char **arvs, int exit_code)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (pwd == NULL)
		pwd = ft_strdup(find_key(data, "PWD")->value);
	write(data->cur_pipe->in_out_fd[1], pwd, ft_strlen(pwd));
	write(data->cur_pipe->in_out_fd[1], "\n", 1);
	free(pwd);
	if (data->cur_pid == 0)
		exit(exit_code);
	else
		g_exit_code = exit_code;
}