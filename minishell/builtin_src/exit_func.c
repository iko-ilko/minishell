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
void	exit_exe(t_vars *vars, char **arvs)
{
	int		exit_code = 0;//임시

	free_vars(vars);
	//릭 정리하고
	//check_arv_number() 는 숫자인지 체크하고 long long 범위 안넘는지 체크
	// if (check_arv_number(arvs) == -1)
	// 	return ;
	exit(exit_code);
}
//세그폴트 뜸뜸
void	free_vars(t_vars *vars)
{
	t_envl	*next_env;

	while (vars->envl != NULL)
	{
		next_env = vars->envl->next;
		free(vars->envl->key);
		free(vars->envl->value);
		free(vars->envl);
		vars->envl = next_env;
	}
	free_single((void **)&vars->pwd);
}

void	free_multi(char **s1, char ***s2, void *p)
{
	int	i;
	
	if (s1 != NULL)
	{
		free(*s1);
		*s1 = NULL;
	}
	i = 0;
	if (*s2 != NULL)
	{
		while ((*s2)[i])
			free((*s2)[i++]);
		free(*s2);
		*s2 = NULL;
	}
	if (p != NULL)
		free(p);
}

void	free_double(char ***str)
{
	int	i;

	i = 0;
	while ((*str)[i])
		free((*str)[i++]);
	free(*str);
	*str = NULL;
}

void	free_single(void **p)
{
	free(*p);
	*p = NULL;
}
