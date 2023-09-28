// 환경변수를 매개인자로 넘겨주면 그 데이터 나오는 함수가 있을 것.
// 2차원 포인터로 넘겨진 char* (커맨드 + 인자들)를 가지고 활용 할 것. -> execve 함수 두번째 인자 처럼.
// 이 함수로 넘어온 데이터는 [0]번째에 무조건 "cd"가 있을 것.
// cd : [1]번째가 NULL일 경우, cd $HOME이 됨.
// cd 디렉토리 : [1]번째가 디렉토리면 그 뒤에 인자들은 처리 안함(bash)
// cd . : 현재 폴더로 이동 -> 일단 엑싯 때려보자.
// cd .. : 이전 폴더로 이동

#include "../minishell.h"

int	get_slash_idx(char *pwd)
{
	int	i;

	i = 0;
	while (pwd[i++])
		;
	while (pwd[--i] != '/')
		;
	return (i);
}

void	change_pwd(t_vars *vars, char *dir)
{
	int		idx;
	char	*temp;

	idx = 0;
	if (dir[0] == '/')
	{
		free(vars->pwd);
		vars->pwd = ft_strdup(dir);
	}
	else if (ft_strcmp(dir, "."))
		return ;
	else if (ft_strcmp(dir, ".."))
	{
		idx = get_slash_idx(vars->pwd);
		temp = vars->pwd;
		if (idx == 0)
			vars->pwd = ft_strdup("/");
		else
			vars->pwd = ft_strndup(vars->pwd, idx);
		free(temp);
	}
}

void	cd_func(char **arvs, t_vars *vars)
{
	if (arvs[1] == NULL)
		return ;
	if (chdir(arvs[1]) == -1)
		perror("minishell: cd: ");
	else
		change_pwd(vars, arvs[1]);
	printf("!%s---%p\n", vars->pwd, vars->pwd);
	printf("?%s---%p\n", getenv("PWD"), getenv("PWD"));
	system("pwd");
}