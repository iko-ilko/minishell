#include "../minishell.h"


void	free_double(char ***str)
{
	int	i;

	i = 0;
	if (*str == NULL)
		return ;
	while ((*str)[i])
	{
		free((*str)[i]);
		(*str)[i++] = NULL;
	}
	free(*str);
	*str = NULL;
}

void	free_single(void **p)
{
	if (p == NULL || *p == NULL)
		return ;
	free(*p);
	*p = NULL;
}

void	free_every(t_data *data, t_info *info, char **line)
{
	free_single((void **)line);
	// if (info->parsing_failed = FAIL)
	// 	return ;
	clear_t_avrl(&info->head);
	clear_t_cmd_node(&data->cmd_node_head);

}
void	close_all_fd(t_pipe *pipe_data)
{
	if (pipe_data->pre_fd[0] != -1)
		close(pipe_data->pre_fd[0]);
	if (pipe_data->pre_fd[1] != -1)
		close(pipe_data->pre_fd[1]);
	if (pipe_data->next_fd[0] != -1)
		close(pipe_data->next_fd[0]);
	if (pipe_data->next_fd[1] != -1)
		close(pipe_data->next_fd[1]);
	if (pipe_data->in_out_fd[0] != 0)
		close(pipe_data->in_out_fd[0]);
	if (pipe_data->in_out_fd[1] != 1)
		close(pipe_data->in_out_fd[1]);
}