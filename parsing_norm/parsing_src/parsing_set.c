/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_set.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwkim2 <jiwkim2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 20:07:30 by jiwkim2           #+#    #+#             */
/*   Updated: 2023/11/24 17:29:39 by jiwkim2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	push_args(t_info *info, char *line)
{
	if (*(info->buff) == 0)
		return ;
	info->content->args[info->args_i] = ft_strdup(info->buff);
	free_single((void *)&info->buff);
	if (line[info->i + 1] != '\0')
		info->buff = get_args_one_size(&line[info->i]);
	if (check_sepa(line[info->i]) == 1)
			info->content->args[info->args_i + 1] = NULL;
	(info->args_i)++;
	info->j = 0;
}

void	set_content(t_info *info, char *line, t_arvl **node, int i)
{
	if (line[info->i] == '>' && line[info->i + 1] == '>' || \
		line[info->i] == '<' && line[info->i + 1] == '<')
		info->i++;
	info->content->flag = i;
	if (*(info->buff) != 0)
		push_args(info, line);
	else
	{
		info->content->args[info->args_i] = NULL;
		ft_lstadd_back(node, ft_lstnew(info->content));
	}
	if (line[info->i + 1] != '\0')
	{
		info->content = ft_calloc(1, sizeof(t_cmd));
		info->content->args = ft_calloc(count_token(line + info->i + 1) + 1, \
		sizeof(char *));
		info->content->flag = 0;
	}
	info->args_i = 0;
}
