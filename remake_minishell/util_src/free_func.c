#include "../minishell.h"

//세그폴트 뜸뜸
void	free_vars(t_data *data)
{
	t_envl	*next_env;

	while (data->envl != NULL)
	{
		next_env = data->envl->next;
		free_single((void *)&data->envl->key);
		free_single((void *)&data->envl->value);
		free(data->envl);
		data->envl = next_env;
	}
	free_single((void **)&data->pwd);
}

void	free_double(char ***str)
{
	int	i;

	i = 0;
	while ((*str)[i])
	{
		free((*str)[i]);
		(*str)[i++] = NULL;
	}
	free(*str);
	*str = NULL;
}

void	free_single(void **p)
{
	if (*p != NULL)
		return ;
	free(*p);
	*p = NULL;
}
