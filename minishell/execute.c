#include "minishell.h"

extern int g_exit_code;

void	execute_child(t_data *data, t_pipe *pipe_data, char **args)
{
	if (args == NULL || args[0] == NULL)
		return ;
	data->cur_pid = fork();
	if (data->cur_pid == -1)
		exit_error("fork error", NULL, 1);
	else if (data->cur_pid == 0)
	{
		signal(SIGQUIT, SIG_DFL);
		if (pipe_data->cmd_idx != 0)
			dup2(pipe_data->pre_fd[0], 0);
		if (pipe_data->cmd_idx != pipe_data->pipe_cnt)
			dup2(pipe_data->next_fd[1], 1);
		if (pipe_data->in_out_fd[0] != 0)
			dup2(pipe_data->in_out_fd[0], 0);
		if (pipe_data->in_out_fd[1] != 1)
			dup2(pipe_data->in_out_fd[1], 1);
		if (if_buitin_func(data, args) == 1)//??여기 빌트인에서 전역변수만 설정하고 여기서 그 값을 리턴하면 각 빌트인 함수에서 굳이 분기 나눌 필요가 .....
			exit(0);
		close_all_fd(pipe_data);
		pipe_data->cur_cmd_path = find_command(args[0], pipe_data->all_path);
		if (ft_strcmp(args[0], "./minishell") == 0)//지워보자
			execve(args[0], args, data->envp);
		else if (execve(pipe_data->cur_cmd_path, args, data->envp) == -1)
		{
			exit_error("command not found", args[0], 127);}
		}
	//여기서 안안에  있있는는것것들  닫닫고  프프리리
}


void	exe_data(t_data *data, char *root_file_name)
{
	t_cmd_node	*cur;
	t_pipe		pipe_data;	

	set_signal(CHILD);
	cur = data->cmd_node_head;
	init_pipe(data, &pipe_data);
	while (cur != NULL)
	{
		data->cur_pipe = &pipe_data;
		if (pipe_data.pipe_cnt != 0)
			set_pipe(data, &pipe_data);
		redirect_file(data->envp, cur->redi, &pipe_data);
		if (next_if_pipe_fail(&pipe_data, &cur) == -1)
			continue ;
		if (cur->args != NULL)//->run_args()
		{
			if (pipe_data.pipe_cnt == 0 && if_buitin_func(data, cur->args) == 1)
				pipe_data.simple_cmd_flag = 1 ;
			else
				execute_child(data, &pipe_data, cur->args);
		}
		if (pipe_data.heredoc_f == 1)
			unlink("here_doc.temp");
		cur = cur->next;
	}
	free_double(&pipe_data.all_path);
	close_all_fd(&pipe_data);
	if (pipe_data.simple_cmd_flag == 0)
		wait_parent(data, &pipe_data);
}

void	wait_parent(t_data *data, t_pipe *pipe_data)
{
	int status_last;
	int	status_others;
	int	signo_last;
	int	signo_others;

	signo_others = 0;
	signo_last = 0;
	status_last = 0;
	status_others = 0;
	waitpid(data->cur_pid, &status_last, 0);
	while (wait(&status_others) != -1)
		;
	if (WIFSIGNALED(status_last) != 0)
	{
		signo_last = WTERMSIG(status_last);
		g_exit_code = 128 + signo_last;
	}
	else
		g_exit_code = WEXITSTATUS(status_last);
	if (signo_last == SIGQUIT)
		write(2, "Quit: 3\n", 8);
}
