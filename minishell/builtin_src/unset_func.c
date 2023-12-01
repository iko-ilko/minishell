/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_func.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilko <ilko@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 15:34:49 by ilko              #+#    #+#             */
/*   Updated: 2023/12/01 15:35:07 by ilko             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

extern int	g_exit_code;

void	unset_exe(t_data *data, char **arvs)
{
	t_envl	*cur;
	t_envl	*pre;
	int		idx;

	idx = 1;
	while (arvs[idx] != NULL)
	{
		if (check_key(arvs[idx], DEL) == -1)
		{
			char *temp = ft_strjoin("unset: ", arvs[idx]);
			str_error("not a valid identifier", temp);
			free_single((void **)&temp);
			g_exit_code = 1;
		}
		else
		{
			cur = data->envl;
			pre = NULL;
			while (cur)
			{
				if (ft_strcmp(cur->key, arvs[idx]) == 0)
				{
					if (pre == NULL)
						data->envl = cur->next;
					else
						pre->next = cur->next;
					free_single((void **)&cur->key);//free_envl함수로 노드한개 또는 전체노드(플래그로 구분할까?)
					free_single((void **)&cur->value);
					free(cur);
					break ;
				}
				pre = cur;
				cur = cur->next;
			}
		}
		idx++;
	}
	free_double(&data->envp);
	update_envp(data, data->envl);
}
