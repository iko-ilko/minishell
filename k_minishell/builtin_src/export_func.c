#include "../minishell.h"

// 출력을 .... value가 NULL이 아니면 = 문자를 출력하자. = 문자까지 입력했다면 value는 ""(빈 문자열)
// bash는 export시 declare -x 가 함께 출력되지만 우리 쉘은 declare 커맨드를 쓰지않을거니 출력 안함.
// shell level 처리 .->할거면 따로 set_env함수 만들어서 shell도 바꿔주고 ..하자. 중요하지 않으니 적당히


// export 파싱은 지우가 주는 데이터 보고 하자.
static int	check_key(char *str)
{
	int	i;

	i = 0;
	if ((str[0] >= 'A' && str[0] <= 'Z') || (str[0] >= 'a' && str[0] <= 'z') || (str[0] == '_'))
		return (0);
	return (1);
}

t_envl	*find_env(t_vars *vars, char *key)
{
	t_envl	*cur;

	cur = vars->envl;
	while (cur)
	{
		if (ft_strcmp(cur->key, key) == 0)
			return (cur);
		cur = cur->next;
	}
	return (NULL);
}

void	modify_env(t_vars *vars, char *key, char *value)
{
	t_envl	*cur;

	cur = vars->envl;
	while (cur)
	{
		if (ft_strcmp(cur->key, key) == 0)
		{
			free(cur->value);
			cur->value = value;
			return ;
		}
		cur = cur->next;
	}
	add_env(vars, key, value);
}

void	add_env(t_vars *vars, char *key, char *value)
{
	t_envl	*cur;
	t_envl	*new;

	new = make_env_node(vars, key, value);
	if (new == NULL)
		error("malloc failed\n", NULL, 1);
	if (vars->envl == NULL)
	{
		vars->envl = new;
		if (vars->envl == NULL)
			error("malloc failed\n", NULL, 1);
		return ;
	}
	if (ft_strcmp(vars->envl->key, key) > 0)
	{
		new->next = vars->envl;
		vars->envl = new;
		return ;
	}
	cur = vars->envl;
	while (cur->next && ft_strcmp(cur->next->key, key) < 0)
		cur = cur->next;
	new->next = cur->next;
	cur->next = new;
}

static void    print_all_export(t_vars *vars)
{
    t_envl  *cur;

    cur = vars->envl;
    while (cur)
    {
		printf("%s", cur->key);
		if (cur->value != NULL)
			printf("=\"%s\"", cur->value);
		
		// if (str_check_space(cur->value) == 1)
		// 	printf("\"%s\"\n", cur->value);
		// else if (cur->value != NULL)
		// 	printf("%s", cur->value);
		printf("\n");
        cur = cur->next;
    }
}

//  / //// 무조건 밸류는 큰따옴표임 ㅠㅠ
void    export_func(t_vars *vars, char **arvs)
{
    int     index;
    char    *key;
    char    *value;

    if (arvs[1] == NULL)
    {
        print_all_export(vars);
        return ;
    }
	// if (check_arv(arvs[1]) == 1) //export 파싱은 지우가 주는 데이터 보고 하자.
	// {
	// 	char *temp = ft_srtjoin("export: ", arvs[1]);

	// 	error("not a valid identifier", temp, 1);
	// }

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
	printf("key:%s\n", key);
	if (check_key(key) == 1)
	{
		char *temp = ft_strjoin("export: ", arvs[1]);
		error("not a valid identifier", temp, 1);
	}
	if (arvs[1][index] == '\0')//여기서부턴 key value 값 만듬
		value = NULL;
	else if(arvs[1][index + 1] == '\0')
		value = ft_strdup("");
	else
        value = ft_strdup(arvs[1] + index + 1);
	if (find_env(vars, key) != NULL)
		modify_env(vars, key, value);
	else
		add_env(vars, key, value);

	// printf("%s", key);//여기서부턴 출력
	// if (value != NULL)
	// 	printf("=");
	// if (str_check_space(value) == 1)
	// 	printf("\"%s\"\n", value);
	// else if (value != NULL)
	// 	printf("%s", value);
	// printf("\n");

    
    // if (index == -2)
    //     key = ft_strdup(arvs[1]);
    // else
    //     key = ft_strndup(arvs[1], index);
    // value = ft_strdup(arvs[1] + index + 1);

    //이 함수는 어차피 위에 함수에서 쓸 것이다. 일단 리스트에 넣어보고 출력값 비교하기.

    
}