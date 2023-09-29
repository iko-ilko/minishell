#include "../minishell.h"

void    envp_to_envl(t_vars *vars, char **envp)
{
    int     i;
    char    *key;
    char    *value;

    i = 0;
    while (envp[i])
    {
        key = ft_strndup(envp[i], ft_strchr(envp[i], '=') - envp[i]);
        value = ft_strdup(ft_strchr(envp[i], '=') + 1);
        list_add_back(&vars->envl, key, value);

        i++;
    }
}