//pwd 뒤에 인자가 몇 개있든 신경 안씀.
// ?? unset PWD 해도 $PWD 값이 있네?
// $PWD, ~ 는 파싱에서 주어진 getcwd(), getenv("HOME") <- 시스템 환경변수에서 들고오는듯.

#include "../minishell.h"

void	pwd_exe(t_vars *vars, char **arvs)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	printf("%s\n", pwd);
	free(pwd);
}