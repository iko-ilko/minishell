/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_second.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwkim2 <jiwkim2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 20:49:38 by jiwkim2           #+#    #+#             */
/*   Updated: 2023/11/22 22:18:24 by jiwkim2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int		double_str_len(char **str)
{
	int idx;

	idx = 0;
	while (str[idx])
		idx++;
	return (idx);
}


char		**parsing_second_args(char **args, char **env)
{
	char *buff;
	int i;
	int idx;
	char *args_temp;

	i = 0;
	idx = 0;
	if (double_str_len(args) == 1)
	{
		buff = set_buff(args[i], env);
		args[0] = word_parsing_splitting(args, &idx, env, buff);
		if (idx== 1)
		{
			args_temp = args[0];
			args = ft_split(args_temp, ' ');
			free(args_temp);
		}
	}
	else
	{
		while (args[idx])
		{
			args[idx] = parsing_args(args[idx], buff, idx, env);
			buff = set_buff(args[idx], env);
			args[idx] = word_parsing(args, &idx, env, buff);
			buff = NULL;
			idx++;
        }
	}
	return(args);
}

void parsing_second(t_arvl *node, char **env)
{
    t_arvl *crr;
    t_cmd *cmd;
    int prev_flag;

	crr = node;
	prev_flag = 0;

	while (crr != NULL)
	{
		if (prev_flag != 5)
		{
			cmd = (t_cmd *)(crr->content);
			cmd->args = parsing_second_args(cmd->args, env);
		}
		prev_flag = cmd->flag;
		crr = crr->next;
	}
}
