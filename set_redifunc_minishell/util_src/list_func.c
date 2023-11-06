#include "../minishell.h"

//연결리스트 만들고 뒤에 붙이는 함수 -> add_envl()로 변경
// void    list_add_back(t_envl **envl, char *key, char *value)
// {
//     t_envl  *new;
//     t_envl  *last;

//     new = (t_envl *)malloc(sizeof(t_envl));
//     if (new == NULL)
// 		exit_error("malloc failed\n", NULL, 1);
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

t_envl	*make_env_node(t_data *data, char *key, char *value)
{
	t_envl	*new;

	new = (t_envl *)malloc(sizeof(t_envl));
	if (new == NULL)
		exit_error("malloc failed\n", NULL, 1);
	new->key = key;
	new->value = value;
	new->next = NULL;
	return (new);
}


t_arvl	*ft_lstnew(void *content)
{
	t_arvl	*res;

	res = (t_arvl *)malloc(sizeof(t_arvl));
	if (res == 0)
		return (0);
	res->content = content;
	res->next = NULL;
	return (res);
}

t_arvl	*ft_lstlast(t_arvl *lst)
{
	while (lst && lst->next != NULL)
		lst = lst->next;
	return (lst);
}

void	ft_lstadd_back(t_arvl **lst, t_arvl *new)
{
	t_arvl	*last;

	if (!*lst)
	{
		*lst = new;
		return ;
	}
	last = ft_lstlast(*lst);
	last->next = new;
}

int	get_lstsize(t_envl *cur)//나중에 다른 구조체에서 쓰인다면 void*와 플래그로
{
	int	i;

	i = 0;
	while (cur != NULL)
	{
		i++;
		cur = cur->next;
	}
	return (i);
}