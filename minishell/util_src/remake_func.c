/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remake_func.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilko <ilko@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 15:40:51 by ilko              #+#    #+#             */
/*   Updated: 2023/12/01 20:39:48 by ilko             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	remake_arvl(t_info *info, t_data *data)
{
	t_arvl	*cur;
	t_cmd	*cur_cmd;

	info->pr_f = -1;
	cur = info->head;
	while (cur)
	{
		cur_cmd = (t_cmd *)cur->content;
		if (next_if_null(&cur, &info->pr_f) == -1)
			continue ;
		if (data->node_open_flag == 0)
			open_new_node(data);
		info->args_i = -1;
		while (cur_cmd->args[++(info->args_i)])
		{
			if (info->args_i == 0 && info->pr_f != PIPE && info->pr_f != -1)
				set_data_redi(data, cur_cmd->args[0], info->pr_f);
			else
				set_data_args(data, cur, info->pr_f, info->args_i);
		}
		if (cur_cmd->flag == PIPE)
			data->node_open_flag = 0;
		info->pr_f = cur_cmd->flag;
		cur = cur->next;
	}
}
