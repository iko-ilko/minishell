/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwkim2 <jiwkim2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 20:58:23 by jiwkim2           #+#    #+#             */
/*   Updated: 2023/11/29 20:50:44 by jiwkim2          ###   ########.fr       */
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

char	*word_parsing(char **a, int *idx, char **env, char *buff)
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
		else if (qt == 0 && (a[*idx][i[I]] == '|' || \
			a[*idx][i[I]] == '>' || a[*idx][i[I]] == '<'))
			break ;
		else if (qt != '\'' && a[*idx][i[I]] == '$' && a[*idx][i[I] + 1])
		{
			buff[i[K]] = '\0';
			if (a[*idx][i[I] + 1] == '?')
				expand_exit_code(&buff, &i[K], &i[I]);
			else
				i[K] = set_env_to_buf(env, find_env(a[*idx], &i[I]), buff);
		}
		else
			buff[(i[K])++] = a[*idx][i[I]];
	}
	return (res_dup(a, buff, i[K], idx));
}
