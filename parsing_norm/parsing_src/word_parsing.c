/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwkim2 <jiwkim2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 20:58:23 by jiwkim2           #+#    #+#             */
/*   Updated: 2023/11/22 22:01:30 by jiwkim2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

extern int g_exit_code;

void		check_split(int *k, int z, int *idx, char quote)
{
	*k = z;
	if (quote != '\"')
		*idx = 1;
}

void expand_exit_code(char **buff, int *k, int *i)
{
    char *ppp = ft_itoa(g_exit_code);
    int zzz = 0;

    while (ppp[zzz])
    {
        (*buff)[*k] = ppp[zzz];
        (*k)++;
        zzz++;
    }

    (*i)++;
    free_single((void **)&ppp);
}

int			set_env_to_buf(char **envv, char *env, char *buf)
{
	int		i;

	i = -1;

	while (envv[++i])
	{
		if (check_unset(env, envv[i]))
		{
			// printf("set_env_to_buf() env:%sbuf:%s\n", env, buf);
			ft_strlcat(buf, \
			envv[i] + ft_strlen(env) + 1, ft_strlen(envv[i]) + ft_strlen(buf));
			break ;
		}
	}
	free(env);
	return ((int)ft_strlen(buf));
}

char		*word_parsing_splitting(char **args, int *idx, char **env, char *buff)
{
    int quote;
	int i;
	int k;
	char *res;

	i = 0;
	quote = 0;
	k = 0;
	while(args[0][i])
    {
		if (args[0][i] == quote)
        quote = 0;
        else if (quote == 0 && (args[0][i] == '\'' || args[0][i] == '\"'))
            quote = args[0][i];
        else if (quote == '\"' && args[0][i] == '\\' && args[0][i + 1] )
            buff[k++] = args[0][++i];
        else if (quote == 0 && args[0][i] == '\\' && args[0][i + 1])
            buff[k++] = args[0][i];
        else if (quote == 0 && ((args[0][i] == '|') || args[0][i] == '>') || (args[0][i] == '<'))
        {
			break;
		}
        else if (quote != '\'' && args[0][i] == '$' && args[0][i + 1])
		{
			buff[k] = '\0';
			if (args[0][i + 1] == '?')
				expand_exit_code(&buff, &k, &i);
			else
            	check_split(&k, set_env_to_buf(env, find_env(args[0], &i), buff), idx, quote);
		}
        else
        {
        	buff[k] = args[0][i];
            	k++;
        }
		i++;
	}
		buff[k] = '\0';
        res = ft_strdup(buff);
        free(buff);
		buff = NULL;
		return(res);
}

char		*word_parsing(char **args, int *idx, char **env, char *buff)
{
	int quote;
	int i;
	int k;
	char *res;

	i = 0;
	quote = 0;
    k = 0;

	while(args[*idx][i])
	{
		if (args[*idx][i] == quote)
			quote = 0;
        else if (quote == 0 && (args[*idx][i] == '\'' || args[*idx][i] == '\"'))
            quote = args[*idx][i];
        else if (quote == '\"' && args[*idx][i] == '\\' && args[*idx][i + 1] )
            buff[k++] = args[*idx][++i];
        else if (quote == 0 && args[*idx][i] == '\\' && args[*idx][i + 1])
            buff[k++] = args[*idx][i];
        else if (quote == 0 && ((args[*idx][i] == '|') || args[*idx][i] == '>') || (args[*idx][i] == '<'))
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
			{
        		buff[k] = args[*idx][i];
				k++;
			}
			i++;
        }
	buff[k] = '\0';
	res = ft_strdup(buff);
	free(buff);
	buff = NULL;
	return(res);
}
