#include "../minishell.h"

// 출력을 .... value가 NULL이 아니면 = 문자를 출력하자. = 문자까지 입력했다면 value는 ""(빈 문자열)
// bash는 export시 declare -x 가 함께 출력되지만 우리 쉘은 declare 커맨드를 쓰지않을거니 출력 안함.
// shell level 처리 .->할거면 따로 set_env함수 만들어서 shell도 바꿔주고 ..하자. 중요하지 않으니 적당히


// export 파싱은 지우가 주는 데이터 보고 하자.
int	check_key(char *str, int unset_flag)
{
	int	i;

	if (!((str[0] >= 'A' && str[0] <= 'Z') || (str[0] >= 'a' && str[0] <= 'z')\
		|| (str[0] == '_')))
		return (-1);
	i = 1;
	while (str[i])
	{
		if (!((str[i] >= 'A' && str[i] <= 'Z') || (str[i] >= 'a' && str[i] <= 'z')\
		|| (str[i] == '_') || (str[i] >= '0' && str[i] <= '9')))
			return (-1);
		i++;
	}
	if (unset_flag == DEL)
	{
		i = 0;
		while(str[i])
		{
			if (str[i++] == '=')
				return (-1);
		}
	}
	return (0);
}

int	find_index(char *str, char c)
{
    int     i;

    i = 0;
    while (str[i])
    {
        if (str[i] == c)
            return (i);
        i++;
    }
    return (0);
}
//OLDPWD 빈거 출력되네? 나중에 체크
static void    print_all_export(t_data *data)
{
    t_envl  *cur;

    cur = data->envl;
    while (cur)
    {
		write(data->cur_pipe->in_out_fd[1], cur->key, ft_strlen(cur->key));
		if (cur->value != NULL)
		{
			write(data->cur_pipe->in_out_fd[1], "\"=", 2);
			write(data->cur_pipe->in_out_fd[1], cur->value, ft_strlen(cur->value));
			write(data->cur_pipe->in_out_fd[1], "\"", 1);
		}
		// if (str_check_space(cur->value) == 1)
		// 	printf("\"%s\"\n", cur->value);
		// else if (cur->value != NULL)
		// 	printf("%s", cur->value);
		write(data->cur_pipe->in_out_fd[1], "\n", 1);
        cur = cur->next;
    }
}
//음 ...함수 빼야하네 ..재귀 안쓰면 수정이 꽤 있을것같으니 재귀는 냅두자 ..
//  / //// 무조건 밸류는 큰따옴표임 ㅠㅠ
//반복문으로 바꾸자 ..
void    export_exe(t_data *data, char **arvs, int idx)
{
    int     index;
    char    *key;
    char    *value;

    if (arvs[1] == NULL)
    {
        print_all_export(data);
        return ;
    }
	if (arvs[idx] == NULL)
		return ;
	// if (check_arv(arvs[1]) == 1) //export 파싱은 지우가 주는 데이터 보고 하자.
	// {
	// 	char *temp = ft_srtjoin("export: ", arvs[1]);

	// 	exit_error("not a valid identifier", temp, 1);
	// }

    //만약 export 하려는 key가 이미 존재하는경우 modify_envp함수에서 밸류만 변경.
    //if (find_key(data->envl, arvs[1]) != NULL)
    //    modify_envp(data, arvs[1], arvs[2]);
    //else
    //    add_envp(data, arvs[1], arvs[2]);

    // int i = 0;
    // while (arvs[i])
    // {
    //     printf("%s\n", arvs[i]);
    //     i++;
    // }
    index = find_index(arvs[idx], '=');//arvs[idx]이 arvs[i]가 되겠지.
	if (index == 0 && arvs[idx][index] != '=')
		index = ft_strlen(arvs[idx]);
    key = ft_strndup(arvs[idx], index);
	if (check_key(key, ADD) == -1)
	{
		char *temp = ft_strjoin("export: ", arvs[idx]);
		str_error("not a valid identifier", temp);
	}
	else
	{
		if (arvs[idx][index] == '\0')//여기서부턴 key value 값 만듬
			value = NULL;
		else if(arvs[idx][index + 1] == '\0')
			value = ft_strdup("");
		else
    	    value = ft_strdup(arvs[idx] + index + 1);
		if (find_key(data, key) != NULL)
			modify_env(data, key, value);
		else
			add_env(data, key, value);

	}
	export_exe(data, arvs, ++idx);
	if (idx == 2)
	{
		printf("update envp!\n");
		free_double(&data->envp);
		update_envp(data, data->envl);
	}

    //이 함수는 어차피 위에 함수에서 쓸 것이다. 일단 리스트에 넣어보고 출력값 비교하기.

    
}
