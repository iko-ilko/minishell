/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwkim2 <jiwkim2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 20:01:09 by jiwkim2           #+#    #+#             */
/*   Updated: 2023/11/29 19:55:09 by jiwkim2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	count_token(char *input)
{
	int		count_token;
	int		sepa_idx;
	char	*p;

	sepa_idx = 0;
	while (check_sepa(input[sepa_idx]) == 0)
		sepa_idx++;
	while (input[sepa_idx] != '\0' && input[sepa_idx] != '|' && \
			input[sepa_idx] != '>' && input[sepa_idx] != '<')
		sepa_idx++;
	p = get_pre_sepa_str(input, sepa_idx);
	count_token = 1;
	if (ft_strtok(p, ' ') != NULL)
	{
		while (ft_strtok(NULL, ' ') != NULL)
			count_token++;
	}
	free(p);
	return (count_token);
}

void	push_i_j(int *i, int *j)
{
	(*i)++;
	(*j)++;
}

void	init_i_j(int *i, int *j)
{
	*i = 0;
	*j = 0;
}

char	*get_args_one_size(char *line, t_info *info)
{
	int		i;
	int		j;
	char	*res;

	init_i_j(&i, &j);
	while (line[i] && ((line[i] >= 0 && line[i] <= 32) || (line[i] == '|') || \
			(line[i] == '>') || (line[i] == '<')))
		i++;
	while (line[i] && (line[i] != '|') && (line[i] != '>') && \
			(line[i] != '<'))
	{
		if (line[i] && (line[i] == '\'' || line[i] == '\"'))
		{
			info->quote = line[i];
			push_i_j(&i, &j);
			while (line[i] && line[i] != info->quote)
				push_i_j(&i, &j);
			info->quote = 0;
		}
		if (line[i])
			push_i_j(&i, &j);
	}
	res = ft_calloc(j + 1, sizeof(char));
	res[j] = '\0';
	return (res);
}
