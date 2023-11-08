#include "minishell.h"
//
void	here_doc(char *limiter, int here_doc_temp_fd)//redirection.c로 보내?말어?
{
	char	*line;
//시그널 처리

	while (1)
	{
		line = readline("> ");//->개행과 EOF도 저장 해줘야 하나?
		//환경변수 확장
		if (!line)
		{
			str_error("readline error", NULL);
			break ;
		}
		if (!ft_strcmp(limiter, line))
			break ;
		write(here_doc_temp_fd, line, ft_strlen(line));
		write(here_doc_temp_fd, "\n", 1);
		free(line);
	}
	free_single((void *)&line);
	close(here_doc_temp_fd);
}

void	execute_child(t_data *data, t_pipe *pipe_data, char **args)
{
	if (args == NULL || args[0] == NULL)
		return ;
	set_pipe(pipe_data);
	data->cur_pid = fork();
	if (data->cur_pid == -1)
		exit_error("fork error", NULL, 1);
	else if (data->cur_pid == 0)
	{
		if (if_buitin_func(data, args) == 1)
		{
			exit(0);//return
		}///
		pipe_data->cur_cmd_path = find_command(args[0], pipe_data->all_path);
		if (ft_strcmp(args[0], "./minishell") == 0)
			execve(args[0], args, data->envp);
		else if (execve(pipe_data->cur_cmd_path, args, data->envp) == -1)
			exit_error("command not found", args[0], 127);
	}
	//여기서 안안에  있있는는것것들  닫닫고  프프리리
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
	t_cmd_node	*cur;
	t_pipe		pipe_data;	

	cur = data->cmd_node_head;
	//init_data
	init_pipe(data, &pipe_data);//need to check
	while (cur != NULL)
	{
		redirect_file(cur->redi, &pipe_data.heredoc_f); //<-히어독 파싱부분에가면 플래그 관련 없애면 됨. 아니면 파싱에서 쓰는 확장 함수 ..재사용 가능할까?
		{
			if (pipe_data.pipe_cnt == 0 && if_buitin_func(data, cur->args) == 1)
				;
			else
				execute_child(data, &pipe_data, cur->args);
		}
		if (pipe_data.heredoc_f == 1)
			unlink("here_doc.temp");
		cur = cur->next;
	}
	wait_parent(data, pipe_data.next_fd);//여기 pre fd 줘도 될것같은데? 아니지 결국 같겠다 나중에 테스트.
}
			// if (ft_strcmp(root_file_name, cmd->args[0]) == 0)//more shell도 그냥 pipex에서 했던 실행에 인자 넣어줘도 될지 체크. 되면 파이프 있는지 체크하고 다른 함수 호출.
			// 	more_shell(data, cmd->args, envp);
			// else if (if_buitin_func(data, cmd->args) == 1)
			// 	;
			//else
			//	execute_argv(data, cmd->content);

//execve("./minishell", arvl->content->args, /*ㄹㅣ스트 다시 2차원 포인터 바꾼 것것*/);