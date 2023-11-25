// 환경변수를 매개인자로 넘겨주면 그 데이터 나오는 함수가 있을 것.
// 2차원 포인터로 넘겨진 char* (커맨드 + 인자들)를 가지고 활용 할 것. -> execve 함수 두번째 인자 처럼.
// 이 함수로 넘어온 데이터는 [0]번째에 무조건 "cd"가 있을 것.
// cd : [1]번째가 NULL일 경우, cd $HOME이 됨.
// cd 디렉토리 : [1]번째가 디렉토리면 그 뒤에 인자들은 처리 안함(bash)
// cd . : 현재 폴더로 이동 -> 일단 엑싯 때려보자.
// cd .. : 이전 폴더로 이동
// cd $없는환경변수 -> cd NULL이기 때문에 홈으로 이동
// 아무래도 getenv()함수는 시스템 환경변수를 들고오니 pipex에서 썼던 find_path를 다듬어서 써야할듯.
// 실제 쉘에서 환경변수 지워도 cd ~, ., .. 가 되는 이유는 Tilde Expansion

// unset한 환경변수는 [iko@host_hp13: home]#cd $HOME
//				-bash: cd: HOME not set 이렇게 출력되는데 mac OS도 그런지 체크하고 그러면 파싱부분에서 cd가 들어오고 없는 환경변수면 -bash: cd: HOME not set 출력 시키기 ..
// 아마도 빌트인 함수라 바로 실행해서 그런듯 ..
#include "../minishell.h"

extern int g_exit_code;

// int	get_slash_idx(char *pwd)
// {
// 	int	i;

// 	i = 0;
// 	while (pwd[i++])
// 		;
// 	while (pwd[--i] != '/')
// 		;
// 	return (i);
// }

// void	change_pwd(t_data *data, char *dir)
// {
// 	int		idx;
// 	char	*temp;

// 	idx = 0;
// 	if (dir[0] == '/')
// 	{
// 		free(data->pwd);
// 		data->pwd = ft_strdup(dir);
// 	}
// 	else if (ft_strcmp(dir, ".") == 0)
// 		return ;
// 	else if (ft_strcmp(dir, "..") == 0)
// 	{
// 		idx = get_slash_idx(data->pwd);
// 		temp = data->pwd;
// 		if (idx == 0)
// 			data->pwd = ft_strdup("/");
// 		else
// 			data->pwd = ft_strndup(data->pwd, idx);
// 		free(temp);
// 	}
// }

void	cd_home(t_data *data, char *error_str)
{
	char	*home_dir;

	home_dir = get_env_value(data, "HOME");
	if (home_dir == NULL)
	{
		if (home_dir == NULL || chdir(home_dir) == -1)
		{
			if (home_dir == NULL)
				str_error("HOME not set anywhere..", "cd");
			else
				perror(error_str);
			g_exit_code = 1;
		}
		printf("???g_exit_code : %d\n", g_exit_code);
	}
	else
	{
		if (chdir(home_dir) == -1)
		{
			perror(error_str);
			g_exit_code = 1;
		}
	}
	free_single((void *)&home_dir);
}

void	set_pwd_env(t_data *data, char *cwd_temp)
{
	char	*temp;

	temp = getcwd(NULL, 0);
	if (temp == NULL || cwd_temp == NULL)
	{
		str_error("getcwd failed", "cd");
		g_exit_code = 1;
		return ;
	}
	modify_env(data, "PWD", ft_strdup(temp));
	modify_env(data, "OLDPWD", cwd_temp);
	free_single((void *)&temp);
}
///////////////일단 리스트 함수들 만들고 export, unset, pwd 명령어 구현하고 cd구현 마무리하자.
//cd $HOME은 파싱 부분에서 확장될것이니까 cd $만 처리하자.
// ㄷㅓ브ㄹ프리남 cd .. 해ㅛㅆㄴㅇ릃 ㄸ깨
void	cd_exe(t_data *data, char **arvs)
{
	char	*error_str;
	char	*cwd_temp;

	error_str = ft_strjoin("minishell: cd: ", arvs[1]);
	cwd_temp = getcwd(NULL, 0);
	if (arvs[1] == NULL || ft_strcmp(arvs[1], "~") == 0)
		cd_home(data, error_str);
	else if (chdir(arvs[1]) == -1)
	{
		perror(error_str);
		g_exit_code = 1;
	}
	if (g_exit_code == 0)
		set_pwd_env(data, cwd_temp);
	free_single((void *)&error_str);
	if (data->cur_pid == 0)
		exit(g_exit_code);
}
