#include "../minishell.h"

void	clear_t_avrl(t_arvl **head)
{
	t_arvl	*cur;
	t_arvl	*next;
	t_cmd	*cmd;

	
	cur = *head;
	while (cur != NULL)
	{
		cmd = cur->content;
		free_double(&cmd->args);
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
		free_double(&cmd->args);
		free(cmd);
		cmd = next;
	}
	*head = NULL;
}

void	clear_t_envl_node(t_envl **head)
{
	t_envl	*cur;
	t_envl	*next;

	cur = *head;
	while (cur != NULL)
	{
		next = cur->next;
		free_single((void **)&cur->key);
		free_single((void **)&cur->value);
		free(cur);
		cur = next;
	}
	*head = NULL;
}