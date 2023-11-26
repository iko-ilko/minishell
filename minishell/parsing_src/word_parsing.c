/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwkim2 <jiwkim2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 20:58:23 by jiwkim2           #+#    #+#             */
/*   Updated: 2023/11/26 17:55:13 by jiwkim2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

extern int	g_exit_code;

void	check_split(int *k, int z, int *idx, char quote)
{
	*k = z;
	if (quote != '\"')
		*idx = 1;
}

void	expand_exit_code(char **buff, int *k, int *i)
{
	char	*exit;
	int		j;

	j = 0;
	exit = ft_itoa(g_exit_code);
	while (exit[j])
	{
		(*buff)[*k] = exit[j];
		(*k)++;
		j++;
	}
	(*i)++;
	free_single((void **)&exit);
}

int	set_env_to_buf(char **envv, char *env, char *buf)
{
	int	i;

	i = -1;
	while (envv[++i])
	{
		if (check_unset(env, envv[i]))
		{
			ft_strlcat(buf, \
			envv[i] + ft_strlen(env) + 1, ft_strlen(envv[i]) + ft_strlen(buf));
			break ;
		}
	}
	free(env);
	return ((int)ft_strlen(buf));
}


char	*word_parsing(char **args, int *idx, char **env, char *buff)
{
	int	quote;
	int	i;
	int	k;
	int	j;

	init_word_parsing(&quote, &i, &k);
	while (args[*idx][++i])
	{
		if (args[*idx][i] == quote)
			quote = 0;
        else if (quote == 0 && (args[*idx][i] == '\'' || args[*idx][i] == '\"'))
            quote = args[*idx][i];
        else if (quote == 0 && ((args[*idx][i] == '|') || args[*idx][i] == '>') || \
			(args[*idx][i] == '<'))
			break;
		else if (quote != '\'' && args[*idx][i] == '$' && args[*idx][i + 1])
		{
			buff[k] = '\0';
			if (args[*idx][i + 1] == '?')
				expand_exit_code(&buff, &k, &i);
			else
				k = set_env_to_buf(env, find_env(args[*idx], &i), buff);
		}
		else
			buff[k++] = args[*idx][i];
	}
	return (res_dup(args, buff, k, idx));
}
