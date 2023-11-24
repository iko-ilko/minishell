#include "../minishell.h"

//세그폴트 뜸뜸
void	free_vars(t_data *data)
{
	t_envl	*next_env;
	t_envl	*cur_env;


	cur_env = data->envl;
	while (cur_env != NULL)
	{
		next_env = cur_env->next;
		free_single((void **)&cur_env->key);
		free_single((void **)&cur_env->value);
		free(cur_env);
		cur_env = next_env;
	}
}

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
	if (*p == NULL)
		return ;

	free(*p);
	*p = NULL;
}

void	clear_t_avrl(t_arvl **head)
{
	t_arvl	*cur;
	t_arvl	*next;
	t_cmd	*cmd;

	cur = *head;
	while (cur != NULL)
	{
		cmd = cur->content;
		free_double((void *)&cmd->args);
		next = cur->next;
		free(cur->content);
		free(cur);
		cur = next;
	}
	*head = NULL;
}

void	clear_t_cmd_node(t_cmd_node **head)
{
	t_cmd_node	*cmd;
	t_cmd_node	*next;
	t_redi		*redi;
	t_redi		*next_redi;

	cmd = *head;
	while (cmd != NULL)
	{
		redi = cmd->redi;
		while (redi != NULL)
		{
			next_redi = redi->next;
			free_single((void *)&redi->file_name);////<-왜 일일차차원
			free(redi);
			redi = next_redi;
		}
		next = cmd->next;
		free_double((void *)&cmd->args);////<-char ***
		free(cmd);
		cmd = next;
	}
	*head = NULL;
}
void	free_every(t_data *data, t_info *info, char **line)
{
	free_single((void **)line);
	clear_t_avrl(&info->head);
	clear_t_cmd_node(&data->cmd_node_head);
	
}
