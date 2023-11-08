#include "../minishell.h"

//세그폴트 뜸뜸
void	free_vars(t_data *data)
{
	t_envl	*next_env;

	while (data->envl != NULL)
	{
		next_env = data->envl->next;
		free_single((void *)&data->envl->key);
		free_single((void *)&data->envl->value);
		free(data->envl);
		data->envl = next_env;
	}
	free_single((void **)&data->pwd);
}

void	free_double(char ***str)
{
	int	i;

	i = 0;
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
	if (*p != NULL)
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
			free_single((void *)&redi->file_name);
			free(redi);
			redi = next_redi;
		}
		next = cmd->next;
		free_double((void *)&cmd->args);
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
