/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_func.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilko <ilko@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 15:10:19 by ilko              #+#    #+#             */
/*   Updated: 2023/12/01 16:35:20 by ilko             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

extern int	g_exit_code;

char	*get_env_value(t_data *data, char *key)
{
	t_envl	*cur;

	cur = data->envl;
	while (cur)
	{
		if (ft_strcmp(cur->key, key) == 0)
			return (cur->value);
		cur = cur->next;
	}
	return (NULL);
}

t_envl	*find_key(t_data *data, char *key)
{
	t_envl	*cur;

	cur = data->envl;
	while (cur)
	{
		if (ft_strcmp(cur->key, key) == 0)
			return (cur);
		cur = cur->next;
	}
	return (NULL);
}

void	modify_env(t_data *data, char *key, char *value)
{
	t_envl	*cur;

	cur = data->envl;
	while (cur)
	{
		if (ft_strcmp(cur->key, key) == 0)
		{
			free_single((void **)&cur->key);
			cur->key = key;
			free_single((void **)&cur->value);
			cur->value = value;
			break ;
		}
		cur = cur->next;
	}
	if (cur == NULL)
		add_env(data, key, value);
	update_envp(data, data->envl);
}

void	add_env(t_data *data, char *key, char *value)
{
	t_envl	*cur;
	t_envl	*new;

	new = make_env_node(data, key, value);
	if (data->envl == NULL)
	{
		data->envl = new;
		return ;
	}
	if (ft_strcmp(data->envl->key, key) > 0)
	{
		new->next = data->envl;
		data->envl = new;
		return ;
	}
	cur = data->envl;
	while (cur->next && ft_strcmp(cur->next->key, key) < 0)
		cur = cur->next;
	new->next = cur->next;
	cur->next = new;
}

void	env_exe(t_data *data, char **arvs)
{
	t_envl	*cur;

	if (arvs[1] != NULL)
	{
		write(2 , "env: ", 5);
		write(2 , arvs[1], ft_strlen(arvs[1]));
		write(2 , ": No Such File or Directory\n", 28);
		g_exit_code = 1;
		return ;
	}
	cur = data->envl;
	while (cur)
	{
		if (cur->value != NULL)
		{
			write(data->cur_pipe->in_out_fd[1], cur->key, ft_strlen(cur->key));
			write(data->cur_pipe->in_out_fd[1], "=", 1);
			write(data->cur_pipe->in_out_fd[1], cur->value, \
			ft_strlen(cur->value));
		}
		write(data->cur_pipe->in_out_fd[1], "\n", 1);
		cur = cur->next;
	}
}
