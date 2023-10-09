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

void	init_exe_data(t_data *data, char **envp, char *root_file)
{
	data->envl = NULL;
    envp_to_envl(data, envp, root_file);
}