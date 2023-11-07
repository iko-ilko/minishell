#include "../minishell.h"
//util/remake_list_func.c
t_redi	*new_redi_last_node(t_redi **head)
{
	t_redi	*new;

	new = (t_redi *)malloc(sizeof(t_redi));
	if (!new)
		exit_error("malloc error", NULL, 1);
	new->flag = 0;
	new->file_name = NULL;
	new->next = NULL;
	if (*head == NULL)
		*head = new;
	else
	{
		while ((*head)->next != NULL)
			*head = (*head)->next;
		(*head)->next = new;
	}
	return (new);
}

t_cmd_node	*new_cmd_last_node(t_cmd_node **head)
{
	t_cmd_node	*new;

	new = (t_cmd_node *)malloc(sizeof(t_cmd_node));
	if (!new)
		exit_error("malloc error", NULL, 1);
	new->redi = NULL;
	new->args = NULL;
	new->next = NULL;
	if (*head == NULL)
		*head = new;
	else
	{
		while ((*head)->next != NULL)
			*head = (*head)->next;
		(*head)->next = new;
	}
	return (new);
}

void	set_data_redi(t_data *data, char *file_name, int pre_flag)
{
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
	if (data->args_i == 0)
		make_exe_args_space(data, cur, pre_flag);
	data->cmd_node_last->args[data->args_i] = ft_strdup(cur_cmd->args[par_i]);
	data->args_i++; //<- 이거 츠가ㅣ함
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
	data->node_open_flag = 0;
	pre_flag = -1;//0으로 해도 되는지 체크
	//인덱스로 커맨드 <-> 노드 연결은 너무 복잡할것같으니 t_cmd에 redi 연결리스트 데이터를 넣어주자.
	cur = info->head;
	while (cur)
	{
		cur_cmd = (t_cmd *)cur->content;
		par_i = 0;
		exe_i = 0;
		if (cur_cmd->args == NULL || cur_cmd->args[0] == NULL)//ㄷㅜㄹ ㅈㅜㅇ ㅎㅏ나만 살살리리기
		{
			pre_flag = cur_cmd->flag;
			cur = cur->next;
			continue ;
		}
		if (data->node_open_flag == 0)
		{
			data->cmd_node_last = new_cmd_last_node(&data->cmd_node_head);
			data->args_i = 0;
			data->node_open_flag = 1;
		}
		while (cur_cmd->args[par_i])
		{
		// printf("args[0] : %s pre_flag:%d\n", cur_cmd->args[0], pre_flag);
			if (par_i == 0 && pre_flag != PIPE && pre_flag != -1)
				set_data_redi(data, cur_cmd->args[0], pre_flag);
			else
				set_data_args(data, cur, pre_flag, par_i);
			par_i++;
			// 	<- cur_cmd 대신 cur 넣고 par_i도 줘야할듯? 다시 생각해보기
			// 위 함함수수들에서 끝인경우 node_open_flag 값올려줘서 아래서 노드 닫기
			// 생각해보니 노드 닫는건 안해도 될듯. 값만 잘 올려주고 calloc쓰면 널 포인터 잘 박혀있을것이고 ..
		}
		printf("-----------------------\n");
		printf("cur->redi->head:%s\n", cur->content) <- 리다이렉션 출출력  해해보보자  이이상상하하게  들들어어간간다다
		print_data_cmd(data);
		printf("-----------------------\n");

		if (cur_cmd->flag == PIPE)
			data->node_open_flag = 0;
		pre_flag = cur_cmd->flag;
		cur = cur->next;
	}//<< limiter cat -e > file | ls | wc > outfile
	//info->head free and NULL
	printf("remake done\n");
}
