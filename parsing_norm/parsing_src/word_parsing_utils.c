/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_parsing_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwkim2 <jiwkim2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 21:15:09 by jiwkim2           #+#    #+#             */
/*   Updated: 2023/11/24 19:18:07 by jiwkim2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	init_set_buff(int *i, int *k)
{
	*i = -1;
	*k = 0;
}

int	check_unset(char *str, char *envv)
{
	int		i;

	i = 0;
	while (str[i] && envv[i] && (str[i] == envv[i]) && (envv[i] != '='))
		i++;
	if ((str[i] == '\0') && (envv[i] == '='))
		return (1);
	return (0);
}

void	init_word_parsing(int *quote, int *i, int *k)
{
	*i = -1;
	*quote = 0;
	*k = 0;
}

char	*res_dup(char **args, char *buff, int k, int *idx)
{
	char	*res;

	free_single((void **)&args[*idx]);
	buff[k] = '\0';
	res = ft_strdup(buff);
	free(buff);
	buff = NULL;
	return (res);
}
