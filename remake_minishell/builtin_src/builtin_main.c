#include "../minishell.h"

//얘네 .... 자식 프로세스에서 실행시키면 에러함수 그냥 엑싯해도 되긴 하는데 ....
//그럼 지우가 준 플래그로 파이프 있으면 각 함수에서 초반에 if_pipe() 해서 파이프 처리 or 안하면 될텐데
// 파이프 뿐만 아니라 리다이렉션이면 표준 입출력 바꿔야한다...
// 리다이렉션은 굳이 파이프 안만들어도 되는게 다른 프로세스로 넘겨주는게 아니라 그냥 파일 디스크립터 바꿔주면 되니까..dup2로
// 위 작업은 굳이 각 함수가 아니라 여기 아래 빌트인 핸들링 하는 함수에서 해도 되겠는데?
int	if_buitin_func(t_data *data, t_pipe *pipe_data, char **arvs)//리다이렉션 때문에write
{
	if (pipe_data->pipe_cnt == 0)
	{
		data->cur_pid = 1;
		data->pipe_temp = pipe_data;
	}각 빌트인에서 출력을 해야하는 경우라면 pid로 분기 나누고 dup2로 자식에서 표준 입출력 바꾸고 pipe_temp에 있는 파일로 dup2(그럼 원래 자식에서 하던거 함수로 빼서 재사용 가능할듯)
	if (ft_strcmp(arvs[0], "cd") == 0)
		cd_exe(data, arvs);
	else if (ft_strcmp(arvs[0], "echo") == 0)
		echo_exe(data, arvs);//child 
	else if (ft_strcmp(arvs[0], "pwd") == 0)
		pwd_exe(data, arvs);//child
	else if (ft_strcmp(arvs[0], "export") == 0)
		export_exe(data, arvs, 1);//child 부분적
	else if (ft_strcmp(arvs[0], "unset") == 0)
		unset_exe(data, arvs, 1);
	else if (ft_strcmp(arvs[0], "env") == 0)
		env_exe(data, arvs);//child
	else if (ft_strcmp(arvs[0], "exit") == 0)
		exit_exe(data, arvs);
	else
		return (0);
	return (1);
}
