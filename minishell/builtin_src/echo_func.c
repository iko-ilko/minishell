#include "../minishell.h"

void	echo_exe(t_data *data, char **arvs)
{
	int	i;
	int	n_flag;

	n_flag = 0;
	if (arvs[1] != NULL && ft_strcmp(arvs[1], "-n") == 0)
		n_flag = 1;
	if (n_flag == 1)
		printf("%s", arvs[1] + 2);
	else
		printf("%s\n", arvs[1]);
}