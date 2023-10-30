#include "minishell.h"
//
void	here_doc(char *limiter)//redirection.c로 보내?말어?
{
	int		here_doc_temp;
	char	*line;
//시그널 처리
	here_doc_temp = open("here_doc.temp", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (here_doc_temp == -1)
	{
		my_perror("here_doc.temp");
		return ;
	}
	while (1)
	{
		line = readline("> ");//->개행과 EOF도 저장 해줘야 하나?
		if (!line)
		{
			str_error("readline error", NULL);
			break ;
		}
		if (!ft_strcmp(limiter, line))
			break ;
		write(here_doc_temp, line, ft_strlen(line));
		free(line);
	}
	free_single((void *)&line);
	close(here_doc_temp);
}

void	execute_child(t_data *data, t_pipe *pipe_data, t_cmd *cmd)
{
	set_pipe(pipe_data);
	data->cur_pid = fork();
	if (data->cur_pid == -1)
		exit_error("fork error", NULL, 1);
	else if (data->cur_pid == 0)
	{
		if (if_buitin_func(data, cmd->args) == 1)
		{
			exit(0);
		}
		pipe_data->cur_cmd_path = find_command(cmd->args[0], pipe_data->all_path);
		if (execve(pipe_data->cur_cmd_path, cmd->args, data->envp) == -1)
			exit_error("command not found", cmd->args[0], 127);
	}
}





// 리다이렉션이 아닌 커맨드의 개수가 하나면서 빌트인 함수면 부모에서 실행.
// 리다이렉션인지 커맨드인지는 플래그로 구분.
// 리다이렉션이면 오는 인자 하나를 파일로 생각.
// < file cat |  wc -w | ls ->     file cat , wc -w, ls 각 노드에 담겨져서 오고 플래그로 구분
// !!아 리다이렉션이 오고 파일이 오면 실행하고 argv의 [1]번째를 커맨드라고 생각할까?
// 위의 예 -> bash-3.2$ < file cat cat cat |  wc | ls
// cat: cat: No such file or directory
// cat: cat: No such file or directory
void	exe_data(t_data *data, char *root_file_name)
{
	t_arvl	*cur;
    t_cmd	*cmd;
	t_pipe	pipe_data;	

	cur = data->arvl;
	init_pipe(data, &pipe_data);
	while (cur != NULL)
	{
		cmd = (t_cmd *)cur->content;
		if (cmd->flag == SIN_REDI_R && cmd->flag == DOUB_REDI_R)
			redirect_file_out(data, &pipe_data, cmd);
		else if (cmd->flag == SIN_REDI_L && cmd->flag == DOUB_REDI_L)
			redirect_file_in(data, &pipe_data, cmd);
		else
		{
			if (pipe_data.pipe_cnt == 0 && if_buitin_func(data, cmd->args) == 1)
				;
			else
				execute_child(data, &pipe_data, cmd);
		}
		if (pipe_data.heredoc_f == 1)
			unlink("here_doc.temp");
		cur = cur->next;
	}
	wait_parent(data, pipe_data.next_fd);
}
			// if (ft_strcmp(root_file_name, cmd->args[0]) == 0)//more shell도 그냥 pipex에서 했던 실행에 인자 넣어줘도 될지 체크. 되면 파이프 있는지 체크하고 다른 함수 호출.
			// 	more_shell(data, cmd->args, envp);
			// else if (if_buitin_func(data, cmd->args) == 1)
			// 	;
			//else
			//	execute_argv(data, cmd->content);

//execve("./minishell", arvl->content->args, /*ㄹㅣ스트 다시 2차원 포인터 바꾼 것것*/);
