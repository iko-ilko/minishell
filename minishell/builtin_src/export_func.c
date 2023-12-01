/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_func.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilko <ilko@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 15:11:12 by ilko              #+#    #+#             */
/*   Updated: 2023/12/01 15:11:12 by ilko             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

extern int	g_exit_code;

int	check_key(char *str, int unset_flag)
{
	int	i;

	if (!((str[0] >= 'A' && str[0] <= 'Z') || (str[0] >= 'a' && str[0] <= 'z') \
		|| (str[0] == '_')))
		return (-1);
	i = 1;
	while (str[i])
	{
		if (!((str[i] >= 'A' && str[i] <= 'Z') || \
			(str[i] >= 'a' && str[i] <= 'z') || \
			(str[i] >= '0' && str[i] <= '9') || (str[i] == '_')))
			return (-1);
		i++;
	}
	if (unset_flag == DEL)
	{
		i = 0;
		while (str[i])
		{
			if (str[i++] == '=')
				return (-1);
		}
	}
	return (0);
}

int	find_index(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	return (0);
}

void	print_all_export(t_data *data)
{
	t_envl	*cur;

	cur = data->envl;
	while (cur)
	{
		write(data->cur_pipe->in_out_fd[1], cur->key, ft_strlen(cur->key));
		if (cur->value != NULL)
		{
			write(data->cur_pipe->in_out_fd[1], "=\"", 2);
			write(data->cur_pipe->in_out_fd[1], cur->value, \
			ft_strlen(cur->value));
			write(data->cur_pipe->in_out_fd[1], "\"", 1);
		}
		write(data->cur_pipe->in_out_fd[1], "\n", 1);
		cur = cur->next;
	}
}

void	export_exe(t_data *data, char **arvs)
{
	int	 index;
	char	*key;
	char	*value;
	int		idx;

	if (arvs[1] == NULL)
	{
		print_all_export(data);
		return ;
	}
	idx = 1;
	while (arvs[idx])
	{
		index = find_index(arvs[idx], '=');//arvs[idx]이 arvs[i]가 되겠지.
		if (index == 0 && arvs[idx][index] != '=')
			index = ft_strlen(arvs[idx]);
		key = ft_strndup(arvs[idx], index);
		if (check_key(key, ADD) == -1)
		{
			char *temp = ft_strjoin("export: ", arvs[idx]);
			str_error("not a valid identifier", temp);
			free_single((void **)&temp);
			g_exit_code = 1;
		}
		else
		{
			if (arvs[idx][index] == '\0')//여기서부턴 key value 값 만듬
				value = NULL;
			else if(arvs[idx][index + 1] == '\0')
				value = ft_strdup("");
			else
			    value = ft_strdup(arvs[idx] + index + 1);
			if (find_key(data, key) != NULL)
				modify_env(data, key, value);
			else
				add_env(data, key, value);

		}
		idx++;
	}
	free_double(&data->envp);
	update_envp(data, data->envl);
}
