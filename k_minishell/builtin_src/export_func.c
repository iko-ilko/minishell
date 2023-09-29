#include "../minishell.h"

static int     find_index(char *str, char c)
{
    int     i;

    i = 0;
    while (str[i])
    {
        if (str[i] == c)
            return (i);
        i++;
    }
    return (1);
}

void    print_all_env(t_vars *vars)
{
    t_envl  *cur;

    cur = vars->envl;
    while (cur)
    {
        printf("\"%s=%s\"\n", cur->key, cur->value);
        cur = cur->next;
    }
}

void    export_func(t_vars *vars, char **arvs)
{
    int     index;
    char    *key;
    char    *value;

    if (arvs[1] == NULL)
    {
        print_all_env(vars);
        return ;
    }
    //만약 export 하려는 key가 이미 존재하는경우 modify_envp함수에서 밸류만 변경.
    //if (find_env(vars, arvs[1]) != NULL)
    //    modify_envp(vars, arvs[1], arvs[2]);
    //else
    //    add_envp(vars, arvs[1], arvs[2]);

    // int i = 0;
    // while (arvs[i])
    // {
    //     printf("%s\n", arvs[i]);
    //     i++;
    // }
    index = find_index(arvs[1], '=');//arvs[1]이 arvs[i]가 되겠지.
    key = ft_strndup(arvs[1], index);
    if (index == ft_strlen(arvs[1]))
        value = ft_strdup("");
    else
        value = ft_strdup(arvs[1] + index + 1);
    
    // if (index == -2)
    //     key = ft_strdup(arvs[1]);
    // else
    //     key = ft_strndup(arvs[1], index);
    // value = ft_strdup(arvs[1] + index + 1);

    //이 함수는 어차피 위에 함수에서 쓸 것이다. 일단 리스트에 넣어보고 출력값 비교하기.
    if (ft_strlen(value) == 0)
        printf("%s\n", key);
    else
        printf("%s=\"%s\"\n", key, value);
    
}