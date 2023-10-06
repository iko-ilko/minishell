//export 는 밸류가 없어도 출력되는데 env는 아님.
//export 는 아스키기준 정렬이 돼서 출력되는데 env는 아님.
//envl에 정렬하지 않고 저장하고, export할때만 정렬해서 출력하자.
//env는 밸밸ㄱ류가 널이면 아예 출력 x. export 는 출력 o

#include "../minishell.h"

void	env_exe(t_vars *vars, char **arvs)
{
	t_envl	*cur;

	cur = vars->envl;
	while (cur)
	{
		if (cur->value != NULL)
			printf("%s=%s\n", cur->key, cur->value);
		cur = cur->next;
	}
}
