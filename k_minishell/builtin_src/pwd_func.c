//pwd 뒤에 인자가 몇 개있든 신경 안씀.
// ?? unset PWD 해도 $PWD 값이 있네?
// $PWD, ~ 는 파싱에서 주어진 getcwd(), getenv("HOME") <- 시스템 환경변수에서 들고오는듯.

#include "../minishell.h"

void	pwd_exe(t_vars *vars, char **arvs)
{
	char	*pwd;
	// t_envl	*pwd_env_node;

	// pwd_env_node = find_env(vars, "PWD");
	// printf("%s\n", pwd_env_node->value);
	// if (pwd_env_node == NULL)
		pwd = getcwd(NULL, 0);
	// else
	// 	pwd = ft_strdup(pwd_env_node->value);
	printf("%s\n", pwd);
	free(pwd);
}