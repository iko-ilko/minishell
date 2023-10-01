#include "../minishell.h"

int	if_buitin_func(t_vars *vars, char *arvs)
{
	if (ft_strcmp(arvs[0], "cd") == 0)
		cd_func(vars, arvs);
	else if (ft_strcmp(arvs[0], "echo") == 0)
		echo_func(vars, arvs);
	else if (ft_strcmp(arvs[0], "pwd") == 0)
		pwd_func(vars, arvs);
	else if (ft_strcmp(arvs[0], "export") == 0)
		export_func(vars, arvs);
	else if (ft_strcmp(arvs[0], "unset") == 0)
		unset_func(vars, arvs);
	else if (ft_strcmp(arvs[0], "env") == 0)
		env_func(vars, arvs);
	else if (ft_strcmp(arvs[0], "exit") == 0)
		exit_func(vars, arvs);
	return (0);
}
