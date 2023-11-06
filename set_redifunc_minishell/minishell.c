#include "minishell.h"

int main(int arc, char **arv, char **envp)
{
	t_info	info;
	t_data	data;
    char    *line;
	int 	i = 0;

	if (arv[1] != NULL)
		exit_error("No such file or directory", arv[1], 127);
    // do_signal();
	init_exe_data(&info, &data, envp, arv[0]);
    signal(SIGINT, sigint_handler);
    signal(SIGQUIT, SIG_DFL);//테스트로 디폴트 작동
    // signal()
	// 빌트인 커맨드 단독 일 때만 부모 프로세스에서 빌트인 실행
    while(1)
    {
        line = readline("minishell$ ");
		if (line == NULL)
			break ;
		// if (ft_strlen(line) == 0)
		// 	continue ;
	    add_history(line);
		parsing(&info, line, data.envp);//리스트에서 바꾼 2차원 배열로
		data.arvl = info.head;
		free(line);
		printf("----------end parsing\n");
		// exe_data(&data, arv[0]);
		//free_all();//with line

    }
}
//함수 잘 빼자 .. if_more_shell() -> shell_child.c , save_history()




// ft_set_buf

// set_env_to_buf


// int		set_env_to_buf(char **envv, char *key, char *buf);
// int 	env_size(char **envv, char *key, int k);
// char	*ft_set_buff(t_cmd *cmd, t_arvl *crr, int idx, char **env);
// void	parsing_second(t_arvl *node, char **env);
