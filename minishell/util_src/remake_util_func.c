/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remake_util_func.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilko <ilko@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 15:40:51 by ilko              #+#    #+#             */
/*   Updated: 2023/12/01 20:39:36 by ilko             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	set_data_redi(t_data *data, char *file_n, int pre_flag)
{
	t_redi	*new;

	new = new_redi_last_node(&data->cmd_node_last->redi);
	new->flag = pre_flag;
	new->file_n = ft_strdup(file_n);
	new->next = NULL;
}

void	make_exe_args_space(t_data *data, t_arvl *cur, int pre_flag)
{
	t_cmd	*cur_cmd;
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

int	next_if_null(t_arvl **cur, int *pre_flag)
{
	t_cmd	*cur_cmd;

	cur_cmd = (t_cmd *)(*cur)->content;
	if (cur_cmd->args == NULL || cur_cmd->args[0] == NULL)
	{
		*pre_flag = cur_cmd->flag;
		*cur = (*cur)->next;
		return (-1);
	}
	return (0);
}
