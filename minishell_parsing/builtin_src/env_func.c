//export 는 밸류가 없어도 출력되는데 env는 아님.
//export 는 아스키기준 정렬이 돼서 출력되는데 env는 아님.
//envl에 정렬하지 않고 저장하고, export할때만 정렬해서 출력하자.
//env는 밸밸ㄱ류가 널이면 아예 출력 x. export 는 출력 o

#include "../minishell.h"

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
			if (cur->value != NULL)
				free(cur->value);
			cur->value = value;
			return ;
		}
		cur = cur->next;
	}
	add_env(data, key, value);
}

void	add_env(t_data *data, char *key, char *value)
{
	t_envl	*cur;
	t_envl	*new;

	new = make_env_node(data, key, value);
	if (new == NULL)
		exit_error("malloc failed\n", NULL, 1);//
	if (data->envl == NULL)
	{
		data->envl = new;
		if (data->envl == NULL)
			exit_error("malloc failed\n", NULL, 1);//
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

	cur = data->envl;
	while (cur)
	{
		if (cur->value != NULL)
			printf("%s=%s\n", cur->key, cur->value);
		cur = cur->next;
	}
}
