#include "../minishell.h"
//util/remake_list_func.c
int aaa = 1;
t_redi	*new_redi_last_node(t_redi **head)
{
	t_redi	*new;
	t_redi	*cur;

	new = (t_redi *)malloc(sizeof(t_redi));
	if (!new)
		exit_error("malloc error", NULL, 1);
	new->flag = 0;
	new->file_name = NULL;
	new->next = NULL;
	cur = *head;
	if (cur == NULL)
		*head = new;
	else
	{
		while ((cur)->next != NULL)
			cur = (cur)->next;
		(cur)->next = new;
	}
	return (new);
}

t_cmd_node	*new_cmd_last_node(t_cmd_node **head)
{
	t_cmd_node	*new;
	t_cmd_node	*cur;

	new = (t_cmd_node *)malloc(sizeof(t_cmd_node));
	if (!new)
		exit_error("malloc error", NULL, 1);
	new->redi = NULL;
	new->args = NULL;
	new->next = NULL;
	cur = *head;
	if (cur == NULL)
		*head = new;
	else
	{
		while ((cur)->next != NULL)
			cur = (cur)->next;
		(cur)->next = new;
	}
	return (new);
}

void	set_data_redi(t_data *data, char *file_name, int pre_flag)
{
	// printf("redi node %d:%s\n", aaa++, file_name);
	t_redi	*new;

	new = new_redi_last_node(&data->cmd_node_last->redi);
	new->flag = pre_flag;
	new->file_name = ft_strdup(file_name);
	new->next = NULL;
}

void	make_exe_args_space(t_data *data, t_arvl *cur, int pre_flag)
{
	t_cmd	*cur_cmd;
	t_cmd	*next_cmd;
	int		exe_args_cnt;
	int		i;

	exe_args_cnt = 0;
	while (cur != NULL)
	{
		i = 0;
		cur_cmd = (t_cmd *)cur->content;
		while (cur_cmd->args[i] != NULL)
		{
			if (i == 0 && pre_flag != PIPE && pre_flag != -1)
				i++;
			if (cur_cmd->args[i] == NULL)
				break ;
			pre_flag = cur_cmd->flag;
			exe_args_cnt++;
			i++;
		}
		if (cur_cmd != NULL && cur_cmd->flag == PIPE)
			break ;
		cur = cur->next;
	} 
	data->cmd_node_last->args = ft_calloc(exe_args_cnt + 1, sizeof(char *));
}

void	set_data_args(t_data *data, t_arvl *cur, int pre_flag, int par_i)
{
	int	i;
	t_cmd	*cur_cmd;

	cur_cmd = (t_cmd *)cur->content;
	// printf("args node %d:%s\n", aaa++, cur_cmd->args[par_i]);
	if (data->args_i == 0)
		make_exe_args_space(data, cur, pre_flag);
	data->cmd_node_last->args[data->args_i] = ft_strdup(cur_cmd->args[par_i]);
	data->args_i++; //<- 이거 츠가ㅣ함
}

void	open_new_node(t_data *data)
{
	data->cmd_node_last = new_cmd_last_node(&data->cmd_node_head);
	data->args_i = 0;
	data->node_open_flag = 1;
}

//앞의 플래그가 리다렉이면 현재 노드의 args[0]을 파일이름으로 생각하고
//리다렉이 아니면 args[0] ~ 현재 노드의 args끝까지를 커맨드로 생각한다.
void	remake_arvl(t_info *info, t_data *data)
{
	t_arvl	*cur;
	t_cmd	*cur_cmd;
	int 	pre_flag;
	int		par_i;

	pre_flag = -1;
	//인덱스로 커맨드 <-> 노드 연결은 너무 복잡할것같으니 t_cmd에 redi 연결리스트 데이터를 넣어주자.
	cur = info->head;
	while (cur)
	{
		cur_cmd = (t_cmd *)cur->content;
		par_i = 0;
		if (cur_cmd->args == NULL || cur_cmd->args[0] == NULL)//ㄷㅜㄹ ㅈㅜㅇ ㅎㅏ나만 살살리리기
		{
			pre_flag = cur_cmd->flag;
			cur = cur->next;
			continue ;
		}
		if (data->node_open_flag == 0)
			open_new_node(data);
		while (cur_cmd->args[par_i])
		{
			if (par_i == 0 && pre_flag != PIPE && pre_flag != -1)
				set_data_redi(data, cur_cmd->args[0], pre_flag);
			else
				set_data_args(data, cur, pre_flag, par_i);
			par_i++;
		}
		if (cur_cmd->flag == PIPE)
			data->node_open_flag = 0;
		pre_flag = cur_cmd->flag;
		cur = cur->next;
	}

	printf("remake done\n");
}
	//<< limiter cat -e > file | ls | wc > outfile
	//info->head free and NULL
