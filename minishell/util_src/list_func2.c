/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_func2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilko <ilko@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 15:40:10 by ilko              #+#    #+#             */
/*   Updated: 2023/12/01 15:40:10 by ilko             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
			free_single((void *)&redi->file_n);
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

t_redi	*new_redi_last_node(t_redi **head)
{
	t_redi	*new;
	t_redi	*cur;

	new = (t_redi *)malloc(sizeof(t_redi));
	if (!new)
		exit_error("malloc error", NULL, 1);
	new->flag = 0;
	new->file_n = NULL;
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