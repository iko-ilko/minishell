#include "../minishell.h"

void    envp_to_envl(t_data *data, char **envp, char *root_file)
{
    int     i;
    char    *key;
    char    *value;
	t_envl	*new;

    i = 0;
    while (envp[i])
    {
        key = ft_strndup(envp[i], ft_strchr(envp[i], '=') - envp[i]);
		if (ft_strcmp(key, "SHELL") == 0)
			value = ft_strdup(root_file);
		else
    	    value = ft_strdup(ft_strchr(envp[i], '=') + 1);
		add_env(data, key, value);
        i++;
    }
	add_env(data, "OLDPWD", NULL);
}

void	update_envp(t_data *data, t_envl *cur)
{
	int		i;
	char	*temp;

	i = 0;
	data->envp = malloc(sizeof(char *) * (get_lstsize(cur) + 1));
	while (cur != NULL)
	{
		if (cur->value == NULL)
			data->envp[i] = ft_strdup(cur->key);
		else if (cur->value[0] == '\0')
			data->envp[i] = ft_strjoin(cur->key, "=");
		else
		{
			temp = ft_strjoin(cur->key, "=");
			data->envp[i] = ft_strjoin(temp, cur->value);
			free(temp);
		}
		cur = cur->next;
		i++;
	}
	data->envp[i] = NULL;
}

void	init_exe_data(t_data *data, char **envp, char *root_file)
{
	data->envl = NULL;
	data->envp = NULL;
    envp_to_envl(data, envp, root_file);
	update_envp(data, data->envl);
}