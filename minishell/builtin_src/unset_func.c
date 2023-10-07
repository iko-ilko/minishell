#include "../minishell.h"

void	unset_exe(t_vars *vars, char **arvs, int idx)
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
		cur = vars->envl;
		pre = NULL;
		while (cur)
		{
			if (ft_strcmp(cur->key, arvs[idx]) == 0)
			{
				if (pre == NULL)
					vars->envl = cur->next;
				else
					pre->next = cur->next;
				free_single((void **)&cur->key);
				free_single((void **)&cur->value);
				free_single((void **)&cur);
				break ;
			}
			pre = cur;
			cur = cur->next;
		}
	}
	unset_exe(vars, arvs, ++idx);
}