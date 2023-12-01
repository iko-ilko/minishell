/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remake_func.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilko <ilko@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 15:40:51 by ilko              #+#    #+#             */
/*   Updated: 2023/12/01 15:44:04 by ilko             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
	int		i;
	t_cmd	*cur_cmd;

	cur_cmd = (t_cmd *)cur->content;
	if (data->args_i == 0)
		make_exe_args_space(data, cur, pre_flag);
	data->cmd_node_last->args[data->args_i] = ft_strdup(cur_cmd->args[par_i]);
	data->args_i++;
}

void	open_new_node(t_data *data)
{
	data->cmd_node_last = new_cmd_last_node(&data->cmd_node_head);
	data->args_i = 0;
	data->node_open_flag = 1;
}

void	remake_arvl(t_info *info, t_data *data)
{
	t_arvl	*cur;
	t_cmd	*cur_cmd;
	int		pre_flag;
	int		par_i;

	pre_flag = -1;
	cur = info->head;
	while (cur)
	{
		cur_cmd = (t_cmd *)cur->content;
		par_i = 0;
		if (cur_cmd->args == NULL || cur_cmd->args[0] == NULL)
		{//next_if_null();
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
}
