/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_first.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwkim2 <jiwkim2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 18:07:06 by jiwkim2           #+#    #+#             */
/*   Updated: 2023/11/29 20:20:44 by jiwkim2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	make_first_init(t_info *info, char *line)
{
	int	count;

	info->args_i = 0;
	info->i = 0;
	info->j = 0;
	info->quote = 0;
	info->head = NULL;
	info->buff = get_args_one_size(line, info);
	info->content = (t_cmd *)malloc(sizeof(t_cmd));
	count = count_token(line);
	info->content->args = ft_calloc(count, sizeof(char *) * (count + 1));
	info->content->flag = 0;
}

void	parsing_check(char *line, t_info *info)
{
	if (line[info->i] == info->quote)
		set_quote(info, 0, line[info->i]);
	else if (info->quote == 0 && (line[info->i] == '\'' || \
		line[info->i] == '\"'))
		set_quote(info, line[info->i], line[info->i]);
	else if (info->quote == 0 && line[info->i] == '|')
		set_content(info, line, &info->head, PIPE);
	else if (info->quote == 0 && line[info->i] == ' ')
		push_args(info, line);
	else if (info->quote == 0 && line[info->i] == '>' && \
		line[info->i + 1] != '>')
		set_content(info, line, &info->head, SIN_REDI_R);
	else if (info->quote == 0 && line[info->i] == '>' && \
		line[info->i + 1] == '>')
		set_content(info, line, &info->head, DOUB_REDI_R);
	else if (info->quote == 0 && line[info->i] == '<' && \
		line[info->i + 1] != '<')
		set_content(info, line, &info->head, SIN_REDI_L);
	else if (info->quote == 0 && line[info->i] == '<' && \
		line[info->i + 1] == '<')
		set_content(info, line, &info->head, DOUB_REDI_L);
	else
		info->buff[info->j++] = line[info->i];
	if (line[info->i + 1] == '\0')
		end_of_line(info, line);
}

int	check_line_error(char *line, int i, int flag)
{
	if (flag == 1 || flag == 3)
		i++;
	if (flag == 2)
		i += 2;
	while (line[i] == ' ')
		i++;
	if (flag == 3)
	{
		if (line[i] == '<' && line[i + 1] == '<')
			return (1);
	}
	if (line[i] == '\0' || line[i] == '|' || line[i] == '<' || line[i] == '>')
		return (0);
	return (1);
}

int	error_case(char *line)
{
	int	i;

	i = -1;
	if (line[0] == '|')
		return (0);
	while (line[++i])
	{
		if ((line[i] == '>' && line[i + 1] == '>') || \
			(line[i] == '<' && line[i + 1] == '<'))
		{
			if (!check_line_error(line, i, 2))
				return (0);
		}
		else if (line[i] == '>' || line[i] == '<')
		{
			if (!check_line_error(line, i, 1))
				return (0);
		}
		else if (line[i] == '|')
		{
			if (!check_line_error(line, i, 3))
				return (0);
		}
	}
	return (1);
}

void	parsing(t_info *info, char *line, char **env)
{
	char	*cmd;

	cmd = ft_strtrim(line, " ");
	if (cmd == NULL || !(error_case(line)))
	{
		info->parsing_failed = FAIL;
		if (cmd == NULL)
			return ;
		free_single((void **)&cmd);
		return (str_error("syntax error", NULL));
	}
	make_first_init(info, cmd);
	while (cmd[info->i])
	{
		parsing_check(cmd, info);
		info->i++;
	}
	if (info->quote != 0)
	{
		info->parsing_failed = FAIL;
		return (str_error("Unclosed quotation mark", NULL));
	}
	parsing_second(info->head, env);
	free_single((void **)&cmd);

}
