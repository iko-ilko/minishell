#include "../minishell.h"
//util/remake_list_func.c
t_cmd_node	*new_redi_node(void)
{
	t_cmd_node	*new;

	new = (t_cmd_node *)malloc(sizeof(t_cmd_node));
	if (!new)
		exit_error("malloc error", NULL, 1);
	new->flag = 0;
	new->fd = 0;
	new->next = NULL;
	return (new);
}

t_cmd_node	*new_cmd_last_node(t_cmd_node **cmd)
{
	t_cmd_node	*new;

	new = (t_cmd_node *)malloc(sizeof(t_cmd_node));
	if (!new)
		exit_error("malloc error", NULL, 1);
	new->redi = NULL;
	new->args = NULL;
	new->next = NULL;
	if (*cmd == NULL)
		*cmd = new;
	else
	{
		while ((*cmd)->next != NULL)
			*cmd = (*cmd)->next;
		(*cmd)->next = new;
	}
	return (new);
}

void	make_exe_args_space(t_data *data, t_arvl *cur)
{
	t_cmd	*cur_cmd;
	int	i;
	int	exe_args_cnt;

	exe_args_cnt = 0;
	while (cur != NULL)
	{
		cur_cmd = (t_cmd *)cur->content;
		i = 0;
		while (cmd->args[i] != NULL)
		{
			exe_args_cnt++;
			i++;
		}
	}
}

void	set_data_cmd(t_data *data, t_cmd *cmd, int pre_flag, t_arvl *cur)
{
	int	i;

	if (data->args_i == 0)
		make_exe_args_space(data, cur);
	i = 0;
	if (pre_flag != PIPE)

	while (cmd->args[i])


	if (cmd->flag == PIPE)
	{
		data->args_i = 0;
		data->cmd = new_cmd_node();
	}
}

//앞의 플래그가 리다렉이면 현재 노드의 args[0]을 파일이름으로 생각하고
//리다렉이 아니면 args[0] ~ 현재 노드의 args끝까지를 커맨드로 생각한다.
void	remake_arvl(t_info *info, t_data *data)
{
	t_arvl	*cur;
	t_cmd	*cur_cmd;
	int 	pre_flag;
	int		par_i;
	int		exe_i;

	data->args_i = 0;
	pre_flag = -1;//0으로 해도 되는지 체크
	//인덱스로 커맨드 <-> 노드 연결은 너무 복잡할것같으니 t_cmd에 redi 연결리스트 데이터를 넣어주자.
	cur = info->head;
	while (cur)
	{
		cur_cmd = (t_cmd *)cur->content;
		pre_flag = cmd->flag;
		par_i = 0;
		exe_i = 0;
		if (cmd->args != NULL && cmd->args[0] != NULL)
		{
			pre_flag = cmd->flag;
			cur = cur->next;
			continue ;
		}
		while (cmd->args[par_i])
		{
			if (par_i == 0 && pre_flag != 0)
				set_data_redi(data, cur_cmd, pre_flag,);
			else
				set_data_cmd(data, cur_cmd, pre_flag, cur);<- cur_cmd 대신 cur 넣고 par_i도 줘야할듯? 다시 생각해보기
		}
			


		cur = cur->next;
	}//<< limiter cat -e > file | ls | wc > outfile
	//info->head free and NULL
}