#include "../minishell.h"

void	unset_exe(t_data *data, char **arvs, int idx)
{
	t_envl	*cur;
	t_envl	*pre;

	if (arvs[idx] == NULL)
		return ;
	if (check_key(arvs[idx], DEL) == -1)
	{
		char *temp = ft_strjoin("unset: ", arvs[idx]);
		str_error("not a valid identifier", temp);
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
				free_single((void **)&cur);
				break ;
			}
			pre = cur;
			cur = cur->next;
		}
	}
	unset_exe(data, arvs, ++idx);
	if (idx == 2)
	{
		printf("update envp!\n");
		free_double(&data->envp);
		update_envp(data, data->envl);
	}
}
