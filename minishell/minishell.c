#include "minishell.h"

int		g_exit_code = 0;

static void	from_left_num(int n, int fd)
{
	char	c;

	if (n / 10 > 0)
		from_left_num(n / 10, fd);
	c = n % 10 + '0';
	write(fd, &c, 1);
}

void	ft_putnbr_fd(int n, int fd)
{
	if (n == -2147483648)
	{
		write(fd, "-2147483648", 11);
		return ;
	}
	if (n < 0)
	{
		write(fd, "-", 1);
		n *= -1;
	}
	from_left_num(n, fd);
}
void	print_data_cmd(t_data *data)
{
	t_cmd_node	*cur;
	t_redi		*redi;
	int			idx = 1;
	int			i;
	cur = data->cmd_node_head;
	while (cur != NULL)
	{
		redi = cur->redi;
		printf("node %d:\n", idx++);
		while (redi != NULL)
		{
			printf("file_name:%s\tredi->flag : %d\n", redi->file_name, redi->flag);
			redi = redi->next;
		}
		if (cur->args != NULL)
		{
			i = 0;
			while (cur->args[i])
			{
				printf("args[%d]:%s \n", i, cur->args[i]);
				i++;
			}
		}
		printf("\n");
		cur = cur->next;
	}
}

int	check_line(char **line)
{
	int		i;
	char	c;

	i = 0;
	if (*line[i++] == '\0')
	{
		free(*line);
		return (-1);
	}
	// while ((*line)[i] != NULL)
	// {
	// 	if ((*line)[i] == '')
	// }
	return (0);
	// 이 함수 제대로 만들기
}
void a()
{
    system("leaks minishell");
}
int main(int arc, char **arv, char **envp)
{
	t_info	info;
	t_data	data;
    char    *line;
	int 	i = 0;


	if (arv[1] != NULL)
		exit_error("No such file or directory", arv[1], 127);
	init_envl(&data, envp, arv[0]);
	// set_signal(PARENT);
	// 빌트인 커맨드 단독 일 때만 부모 프로세스에서 빌트인 실행
	// rl_catch_signals = 0;
    while(1)
    {
		set_signal(PARENT);
	// signal(SIGINT, parent_sigint_handler);
	// signal(SIGQUIT, SIG_IGN);
        line = readline("minishell$ ");
		if (line == NULL)//<-파상 안에서 하는 trim 여기서 할까? 아님 파싱에서 syntax error 잡히면 -1 리턴하고 그러면 라인 free하고 continue되게 할까?
			break ;
		if (check_line(&line) == -1)
			continue ;
	    add_history(line);
		every_init(&info, &data);
		parsing(&info, line, data.envp);
		// print_nodes_to_head(info.head); //print info->head
		remake_arvl(&info, &data);
		// print_data_cmd(&data);//print data->cmd_node_head
		// printf("----------end parsing\n");
		// set_signal(CHILD);//<---이가 왜 메인으로 빼니까 되냐ㅡㅡ

		exe_data(&data, arv[0]);//root file name 필요없을듯 있으면 구조체에 ㄱ
		free_every(&data, &info, &line);//with line
    }
	// atexit(a);
}
//함수 잘 빼자 .. if_more_shell() -> shell_child.c , save_history()




// ft_set_buf

// set_env_to_buf


// int		set_env_to_buf(char **envv, char *key, char *buf);
// int 	env_size(char **envv, char *key, int k);
// char	*ft_set_buff(t_cmd *cmd, t_arvl *crr, int idx, char **env);
// void	parsing_second(t_arvl *node, char **env);
