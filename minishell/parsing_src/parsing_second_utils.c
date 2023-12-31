/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_second_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilko <ilko@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 20:52:41 by jiwkim2           #+#    #+#             */
/*   Updated: 2023/12/01 17:37:16 by ilko             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

extern int	g_exit_code;

int	get_exit_code_len(int g_exit_code)
{
	int	len;
	int	temp;

	if (g_exit_code == 0)
		return (1);
	temp = g_exit_code;
	len = 0;
	while (temp)
	{
		temp /= 10;
		len++;
	}
	return (len);
}

void	move_env_size(char **envv, char *env, int *k)
{
	int	i;
	int	env_len;

	i = 0;
	env_len = ft_strlen(env);
	while (envv[i])
	{
		if (ft_strncmp(envv[i], env, env_len) == 0)
		{
			if (envv[i][env_len] == '=')
				*k += ft_strlen(envv[i] + env_len + 1);
			break ;
		}
		i++;
	}
	free (env);
}

void	init_word_parsing(int *quote, int i_k[2])
{
	i_k[I] = -1;
	i_k[K] = 0;
	*quote = 0;
}

char	*find_env(char *str, int *j)
{
	char	*res;
	int		i;

	(*j)++;
	i = *j;
	while (str[i] && str[i] != '$' && ft_isalnum(str[i]))
		i++;
	i--;
	res = ft_strndup(str + *j, i - *j + 1);
	*j = i;
	return (res);
}

char	*set_buff(char *args_line, char **env)
{
	int	i;
	int	k;

	init_set_buff(&i, &k);
	while (args_line[++i])
	{
		if (args_line[i] == '$' && args_line[i + 1])
		{
			k--;
			if (args_line[i + 1] == '?')
				k += get_exit_code_len(g_exit_code);
			else if (!(ft_isalnum(args_line[i + 1])))
				k++;
			else
			{
				move_env_size(env, find_env(args_line, &i), &k);
				i--;
				continue ;
			}
		}
		else
			k++;
	}
	return (make_buff(k));
}
