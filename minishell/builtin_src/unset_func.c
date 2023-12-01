/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_func.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilko <ilko@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 15:34:49 by ilko              #+#    #+#             */
/*   Updated: 2023/12/01 20:01:53 by ilko             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

extern int	g_exit_code;

void	invaild_identifier(char *arv, int flag)
{
	char	*temp;

	if (flag == ADD)
	{
		temp = ft_strjoin("export: ", arv);
		str_error("not a valid identifier", temp);
		free_single((void **)&temp);
	}
	else
	{
		temp = ft_strjoin("unset: ", arv);
		str_error("not a valid identifier", temp);
		free_single((void **)&temp);
	}
	g_exit_code = 1;
}

void	roop_in_unset(t_data *data, char *arv)
{
	t_envl	*cur;
	t_envl	*pre;

	cur = data->envl;
	pre = NULL;
	while (cur != NULL)
	{
		if (ft_strcmp(cur->key, arv) == 0)
		{
			if (pre == NULL)
				data->envl = cur->next;
			else
				pre->next = cur->next;
			free_single((void **)&cur->key);
			free_single((void **)&cur->value);
			free(cur);
			cur = NULL;
			break ;
		}
		pre = cur;
		cur = cur->next;
	}
}

void	unset_exe(t_data *data, char **arvs)
{
	t_envl	*cur;
	t_envl	*pre;
	int		idx;

	idx = 1;
	while (arvs[idx] != NULL)
	{
		if (check_key(arvs[idx], DEL) == -1)
			invaild_identifier(arvs[idx], DEL);
		else
			roop_in_unset(data, arvs[idx]);
		idx++;
	}
	free_double(&data->envp);
	update_envp(data, data->envl);
}
