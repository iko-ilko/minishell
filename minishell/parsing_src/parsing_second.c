/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_second.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwkim2 <jiwkim2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 20:49:38 by jiwkim2           #+#    #+#             */
/*   Updated: 2023/11/25 20:44:12 by jiwkim2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	double_str_len(char **str)
{
	int	idx;

	idx = 0;
	while (str[idx])
		idx++;
	return (idx);
}

char	**parsing_second_args(char **args, char **env)
{
	char	*buff;
	int		idx;

	idx = 0;
	while (args[idx])
	{
		buff = set_buff(args[idx], env);
		args[idx] = word_parsing(args, &idx, env, buff);
		buff = NULL;
		idx++;
	}
	return (args);
}

char	*word_parsing_heredoc(char **a, int *idx, char **env, char *buff)
{
	int	qt;
	int	i[2];

	init_word_parsing(&qt, i);
	while (a[*idx][++i[I]])
	{
		if (a[*idx][i[I]] == qt)
			qt = 0;
		else if (qt == 0 && (a[*idx][i[I]] == '\'' || a[*idx][i[I]] == '\"'))
			qt = a[*idx][i[I]];
		else
			buff[(i[K])++] = a[*idx][i[I]];
	}
	return (res_dup(a, buff, i[K], idx));
}

char	**here_doc_parsing(char **args, char **env)
{
	char	*buff;
	int		idx;

	idx = 0;
	while (args[idx])
	{
		if (idx == 0)
		{
			buff = set_buff_heredoc(args[0]);
			args[idx] = word_parsing_heredoc(args, &idx, env, buff);
			buff = NULL;
			idx++;
		}
		else
		{
			buff = set_buff(args[idx], env);
			args[idx] = word_parsing(args, &idx, env, buff);
			buff = NULL;
			idx++;
		}
	}
	return (args);
}

void	parsing_second(t_arvl *node, char **env)
{
	t_arvl	*crr;
	t_cmd	*cmd;
	int		prev_flag;

	crr = node;
	prev_flag = 0;
	while (crr != NULL)
	{
		cmd = (t_cmd *)(crr->content);
		if (prev_flag != 5)
		{
			cmd->args = parsing_second_args(cmd->args, env);
		}
		if (prev_flag == 5)
			cmd->args = here_doc_parsing(cmd->args, env);
		prev_flag = cmd->flag;
		crr = crr->next;
	}
}
