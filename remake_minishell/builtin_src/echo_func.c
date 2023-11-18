#include "../minishell.h"

void	echo_exe(t_data *data, char **arvs)
{
	int	n_flag;
	int	i;

	n_flag = 0;
	if (arvs[1] != NULL && ft_strcmp(arvs[1], "-n") == 0)
		n_flag = 1;
	i = n_flag + 1;
	while (arvs[i] != NULL)
		printf("%s ", arvs[i++]);//공백 기준으로 args 나눠져있을테니 일단 이렇게하고 계속 테스트 해보기(마지막 분기도 나눠야할듯)
	if (n_flag == 0)
		printf("\n");

}
