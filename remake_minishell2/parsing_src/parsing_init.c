/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwkim2 <jiwkim2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 20:01:09 by jiwkim2           #+#    #+#             */
/*   Updated: 2023/11/22 21:06:01 by jiwkim2          ###   ########.fr       */
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

char	*get_args_one_size(char *line)
{
	int		i;
	int		j;
	char	*res;

	i = 0;
	j = 0;
	while (line[i] && ((line[i] >= 0 && line[i] <= 32) || (line[i] == '|') || \
			(line[i] == '>') || (line[i] == '<')))
	{
		i++;
	}
	while (line[i] && (line[i] != '|') && (line[i] != '>' && \
			(line[i] != '<')))
	{
			i++;
			j++;
	}
	res = ft_calloc(j + 1, sizeof(char));
	res[j] = '\0';
	return (res);
}
