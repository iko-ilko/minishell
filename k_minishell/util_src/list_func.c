#include "../minishell.h"

//연결리스트 만들고 뒤에 붙이는 함수 -> add_envl()로 변경
// void    list_add_back(t_envl **envl, char *key, char *value)
// {
//     t_envl  *new;
//     t_envl  *last;

//     new = (t_envl *)malloc(sizeof(t_envl));
//     if (new == NULL)
// 		error("malloc failed\n", NULL, 1);
//     new->key = key;
//     new->value = value;
//     new->next = NULL;
//     if (*envl == NULL)
//         *envl = new;
//     else
//     {
//         last = *envl;
//         while (last->next != NULL)
//             last = last->next;
//         last->next = new;
//     }
// }

t_envl	*make_env_node(t_vars *vars, char *key, char *value)
{
	t_envl	*new;

	new = (t_envl *)malloc(sizeof(t_envl));
	if (new == NULL)
		error("malloc failed\n", NULL, 1);
	new->key = key;
	new->value = value;
	new->next = NULL;
	return (new);
}
