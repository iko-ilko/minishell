/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilko <ilko@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 15:36:12 by ilko              #+#    #+#             */
/*   Updated: 2023/12/01 15:36:12 by ilko             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*res_dup_one(char *args, char *buff, int k)
{
	char	*res;

	free_single((void **)&args);
	buff[k] = '\0';
	res = ft_strdup(buff);
	free(buff);
	buff = NULL;
	return (res);
}

char	*word_parsing_splitting(char *args, char **env, char *buff)
{
	int	i;
	int	k;

	i = -1;
	k = 0;
	while (args[++i])
	{
		if (args[i] == '$' && args[i + 1])
		{
			buff[k] = '\0';
			if (args[i + 1] == '?')
				expand_exit_code(&buff, &k, &i);
			else
			k = set_env_to_buf(env, find_env(args, &i), buff);
		}
		else
			buff[k++] = args[i];
	}
	return (res_dup_one(args, buff, k));
}

char	*parsing_second_args_tt(char *args, char **env)
{
	char	*buff;
	int		i;

	i = 0;
	buff = set_buff(args, env);
	args = word_parsing_splitting(args, env, buff);
	return (args);
}

void	here_doc(char **envp, char *limiter, int here_doc_temp_fd)
{
	char	*line;
	int		i;

	set_signal(HEREDOC);
	while (1)
	{
		line = readline("> ");
		if (line == NULL)
			return ;
		if (!ft_strcmp(limiter, line))
			break ;
		i = -1;
		while (line[++i])
		{
			line = parsing_second_args_tt(line, envp);
			if (line[0] == '\0')
				break ;
		}
		write(here_doc_temp_fd, line, ft_strlen(line));
		write(here_doc_temp_fd, "\n", 1);
		free(line);
	}
	free_single((void *)&line);
	close(here_doc_temp_fd);
	set_signal(CHILD);
}
