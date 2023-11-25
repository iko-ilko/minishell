/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_init_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwkim2 <jiwkim2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 20:02:58 by jiwkim2           #+#    #+#             */
/*   Updated: 2023/11/22 21:49:58 by jiwkim2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	end_of_line(t_info *info, char *line)
{
	push_args(info, line);
	ft_lstadd_back(&info->head, ft_lstnew(info->content));
}

void	set_quote(t_info *info, char quot, char buffer)
{
	info->quote = quot;
	info->buff[info->j++] = buffer;
	if (info->quote == 0)
		info->buff[info->j] = '\0';
}

int	check_sepa(char c)
{
	if (c == '|' || c == '>' || c == '<' || c == '\0')
		return (1);
	return (0);
}

char	*get_pre_sepa_str(char *input, int sepa_idx)
{
	char	*res;
	int		i;

	res = ft_calloc(sepa_idx + 1, sizeof(char));
	i = 0;
	while (i < sepa_idx)
	{
		res[i] = input[i];
		i++;
	}
	res[i] = '\0';
	return (res);
}
