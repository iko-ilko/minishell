#include "../minishell.h"

//연결리스트 만들고 뒤에 붙이는 함수
void    list_add_back(t_envl **lst, char *key, char *value)
{
    t_envl  *new;
    t_envl  *last;

    new = (t_envl *)malloc(sizeof(t_envl));
    if (new == NULL)
		error("malloc failed\n", NULL, 1);
    new->key = key;
    new->value = value;
    new->next = NULL;
    if (*lst == NULL)
        *lst = new;
    else
    {
        last = *lst;
        while (last->next != NULL)
            last = last->next;
        last->next = new;
    }
}
