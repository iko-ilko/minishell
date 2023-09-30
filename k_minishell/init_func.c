#include "minishell.h"

void    envp_to_envl(t_vars *vars, char **envp)
{
    int     i;
    char    *key;
    char    *value;
	t_envl	*new;

    i = 0;
    while (envp[i])
    {
        key = ft_strndup(envp[i], ft_strchr(envp[i], '=') - envp[i]);
        value = ft_strdup(ft_strchr(envp[i], '=') + 1);
		add_env(vars, key, value);
        i++;
    }
}

void	init_exe_data(t_vars *vars, char **envp)
{
	vars->envl = NULL;
    envp_to_envl(vars, envp);
}