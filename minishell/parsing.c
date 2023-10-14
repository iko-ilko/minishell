#include "minishell.h"

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*p;
	size_t			i;

	i = 0;
	p = (unsigned char *)b;
	while (i < len)
	{
		*p = (unsigned char)c;
		p++;
		i++;
	}
	return ((void *)b);
}

void set_quote(t_info *info, char quot, char buffer)
{
	info->quote = quot;
	info->buff[info->j++] = buffer;
	if (info->quote == 0)
		info->buff[info->j] = '\0';
}




char	*ft_strtok(char *str, char sepa)
{
	static char	*stock = NULL;
	char		*p;
	int			i;

	i = 0;
	p = NULL;
	if (str != NULL)
		stock = ft_strdup(str);
	while (*stock != '\0')
	{
		if (i == 0 && *stock != sepa)
		{
			i = 1;
			p = stock;
		}
		else if (i == 1 && *stock == sepa)
		{
			*stock = '\0';
			stock += 1;
			break ;
		}
		stock++;
	}
	return (p);
}


int		count_token(char *input)
{
	int		count_token;
	char	*p;

	count_token = 1;
	if (!(p = ft_calloc(ft_strlen(input) + 1, sizeof(char))))
		return (0);
	ft_strcpy(p, input);
	if (ft_strtok(p, ' ') != NULL)
	{
		while (ft_strtok(NULL, ' ') != NULL)
			count_token++;
	}
	free(p);
	return (count_token);
}

char *ft_size_check(char *line)
{
	int i;
	int j;
	char *res;

	i = 0;
	j = 0;
	while (line[i] && ((line[i] >= 0 && line[i] <= 32) || (line[i] == '|') || ( line[i] == ';') || \
			(line[i] == '>') || (line[i] == '>')))
	{
		i++;
	}
	while (line[i] && ((line[i] != ' ') && (line[i] != '|') && ( line[i] != ';') && (line[i] != '>' && \
			(line[i] != '<'))))
		{
			i++;
			j++;
		}
	res = (char *)malloc((j + 1) * sizeof(char));
	res[j] = '\0';
	return (res);
}

void	push_args(t_info *info, char *line)
{
	if (*(info->buff) == 0)
		return ;
	info->content->args[info->args_i] = ft_strdup(info->buff);
	info->content->args[info->args_i + 1] = NULL;
	(info->args_i)++;
	free(info->buff);
	ft_memset(info->buff, 0, ft_strlen(info->buff) + 1);
	info->buff = ft_size_check(&line[info->i]);
	info->j = 0;
}

void		set_content(t_info *info, char *line, t_arvl **node, int i)
{
	if (line[info->i] == '>' && line[info->i + 1] == '>' || line[info->i] == '<' && \
		line[info->i + 1] == '<')
		info->i++;
	if (line[info->i + 1] != '\0' && (line[info->i + 1] == '>' || line[info->i + 1] == '<' || \
		line[info->i + 1] == '|' || line[info->i + 1] == ';'))
	{
		printf("syn error\n");
		exit(1);	
	}
	info->content->flag = i;
	if (*(info->buff) != 0)
		push_args(info, line);
	if ((info->content->args)[0] == 0 && info->content->flag <= 1)
		exit(0);
	else
	{
		ft_lstadd_back(node, ft_lstnew(info->content));
		info->content = ft_calloc(1, sizeof(t_cmd));
		info->content->args = ft_calloc(count_token(line) + 1, sizeof(char *));
		info->content->flag = 0;
	}
	info->args_i = 0;
}



char	*ft_substr(char *s, unsigned int start, size_t len)
{
	int		i;
	char	*res;

	printf("ft_substr() start:%d, len:%d\n", start, (int)len);
	if (len == 0)
	{
		res = malloc(sizeof(char));
		//if (res == 0) exit_error("mal ", 1)
		*res = 0;
		return (res);
	}
	if ((res = (char *)malloc(sizeof(char) * (len + 1))) == 0)
		return (0);
	i = 0;
	if (start < (unsigned int)ft_strlen(s))
	{
		while (len--)
			res[i++] = s[start++];
	}
	res[i] = '\0';
	printf("ft_substr() i:%dres:%s\n", i, res);
	return (res);
}


char	*ft_strtrim(char *s1, char *set)
{
	size_t	start;
	size_t	end;
	char	*res;

	start = 0;
	if (s1 == 0 || set == 0)
		return (0);
	end = ft_strlen(s1);
	while (s1[start] && ft_strchr(set, s1[start]))
			start++;
	while (s1[end - 1] && ft_strchr(set, s1[end - 1]))
			end--;
	if (start > end)
		return (ft_strdup(""));
	res = ft_substr(s1, start, end - start);
	return (res);
}

void parsing_check(char *line, t_info *info)
{
    if (line[info->i] == info->quote)
        set_quote(info, 0, line[info->i]);
    else if (info->quote == 0 && (line[info->i] == '\'' || line[info->i] == '\"'))
        set_quote(info, line[info->i], line[info->i]);
    else if (info->quote == 0 && line[info->i] == '|')
        set_content(info, line, &info->head, PIPE);
    else if (info->quote == 0 && line[info->i] == ';')
        set_content(info, line, &info->head, SEMICOLON_NONE);//같은 이유가 뭘까
    else if (info->quote == 0 && line[info->i] == ' ')
        push_args(info, line); 
    else if (info->quote == 0 && line[info->i] == '>' && line[info->i + 1] != '>')
        set_content(info, line, &info->head, SI_REDI_R);
    else if (info->quote == 0 && line[info->i] == '>' && line[info->i] == '>')
        set_content(info, line, &info->head, DOUB_REDI_R);
    else if (info->quote == 0 && line[info->i] == '<' && line[info->i + 1] != '<')
        set_content(info, line, &info->head, SI_REDI_L);
    else if (info->quote == 0 && line[info->i] == '<' && line[info->i + 1] == '<')
        set_content(info, line, &info->head, DOUB_REDI_L);
    else if (info->quote == '\"' && line[info->i] == '\\')
    {
        info->buff[info->j++] = line[info->i];
        info->i++;
        info->buff[info->j++] = line[info->i];
    }
	// else if (info->quote == 0 && line[info->i] == '\\')
    // {
    //     info->i++;
        //     info->buff[info->j++] = line[info->i];
    // }
    else
        info->buff[info->j++] = line[info->i];

}


void parsing_init(t_arvl **node, t_info *info, char *line)
{
	info->args_i = 0;
	info->i = 0;
	info->j = 0;
	*node = NULL;
	//*node = ft_lstnew(NULL);
	// info->head = *node;
	info->quote = 0;
	info->buff = ft_size_check(line);
	info->content = (t_cmd *)malloc(sizeof(t_cmd));
	info->content->args = (char **)malloc((count_token(line) + 1) * sizeof(char*));
	info->content->flag = 0;
}


int	ft_isalnum(int c)
{
	if (((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))
		|| ((c >= '0') && (c <= '9')))
		return (1);
	else
		return (0);
}

/* key의 길이 + 1($문자) 만큼 인덱스를 밀어주면서, $를 제외한 키의 문자열을 반환 *//* i는 달러 위치 */
/* e.x)  $USER *i의 값은 + 5만큼 해주고 USER를 반환 */
/* parsing env key of args */
char		*find_env(char *str, int *j)
{
	// char	*res;

	// *j += ft_strlen(str + 1) + 1;
	// res = ft_strdup(str + 1);
	// printf("find_env() j:%dres:%s\n", *j, res);
	// return (res);
	// // return (ft_strdup(str + 1));



	
	char	*ret;
	int		start;
	int		idx;

	idx = *j + 1;
	start = *j + 1;
	while (str[idx])
		if (ft_isalnum(str[idx]))
			idx++;
		else
		{
			idx--;
			break ;
		}
	*j = idx;
	ret = ft_substr(str, start, idx - start);
	printf("find_env()idx:%d, ret:%s, str:%sidx-start+1:%d\n", idx, ret, str, idx - start);
	return (ret);
}

size_t  ft_strlcat(char *dst, char *src, size_t dstsize)
{
        size_t  i;
        size_t  dst_len;
        size_t  src_len;
	printf("dst:%s src:%s dstsize:%d\n", dst, src, (int)dstsize);

        src_len = ft_strlen(src);
        if (dstsize == 0)
                return (src_len);
        dst_len = ft_strlen(dst);
        if (dst_len + 1 > dstsize)
                return (src_len + dstsize);
        i = 0;
        while (dst_len + i < dstsize - 1 && src[i])
        {
                dst[dst_len + i] = src[i];
                i++;
        }
        dst[dst_len + i] = '\0';
        return (src_len + dst_len);
}
// size_t	ft_strlcat(char *dst, char *src, size_t dstsize)
// {
// 	size_t	a;
// 	size_t	b;
// 	char	*c;
// 	printf("dst:%s src:%s dstsize:%d\n", dst, src, (int)dstsize);
// 	a = 0;
// 	b = 0;
// 	c = (char *)src;
// 	if (dstsize == 0)
// 		return (ft_strlen(src) + dstsize);
// 	while (dst[a] != '\0')
// 		a++;
// 	while (c[b] != '\0' && a + b + 1 < dstsize)
// 	{
// 		dst[a + b] = c[b];
// 		b++;
// 	}
// 	dst[a + b] = '\0';
// 	if (dstsize <= ft_strlen(dst))
// 		return (ft_strlen(src) + dstsize);
// 	else
// 		return (ft_strlen(src) + a);
// }

/* key만큼 실제 buf */
int	check_unset(char *str, char *envv)
{
	int		i;

	i = 0;
	while (str[i] && envv[i] && (str[i] == envv[i]) && (envv[i] != '='))
		i++;
	if ((str[i] == '\0') && (envv[i] == '='))
		return (1);
	return (0);
}
/* lcat에서 실제로 환경변수가 확장돼서 나온다. */
int			set_env_to_buf(char **envv, char *env, char *buf)
{
	int		i;

	i = -1;
	printf("확장전 buf 길이:%dbuf:%s\n", (int)ft_strlen(buf), buf);

	while (envv[++i])
	{
		if (check_unset(env, envv[i]))
		{
			printf("set_env_to_buf() env:%s\n", env);
			ft_strlcat(buf, \
			envv[i] + ft_strlen(env) + 1, ft_strlen(envv[i]) + ft_strlen(buf));
			break ;
		}
	}
	free(env);
	printf("확장하고 나온 buf 길이:%dbuf:%s\n", (int)ft_strlen(buf), buf);
	return ((int)ft_strlen(buf));
}

void		check_split(int *k, int z, int *idx, char quote)
{
	*k = z;
	if (quote != '\"')
		*idx = 1;
}

/* key의 길이를 리턴 */
int         check_unset_sub(char *str, char *envv)
{
    int     i;
    i = 0;
    while (str[i] && envv[i] && (str[i] == envv[i]) && (envv[i] != '='))
        i++;
    if ((str[i] == '\0') && (envv[i] == '='))
    {
        i++;
        return (i);
    }
    return (0);
}
/* 버퍼 만들 때 밸류의 길이 k: value의 길이*/
int env_size(char **envv, char *env, int k)
{
    int i;
    int j;
    i = 0;
    j = 0;
    while (envv[i])
    {
        j = check_unset_sub(env, (char*)envv[i]);
        if (j != 0)
        {
            while (envv[i][j])
            {
                j++;
                k++;
            }
        }
        i++;
    }
	printf("env_size() k:%denv:%s\n", k, env);
    return(k);
}
/* second_parsing() 함수에서 호출하고, 마지막으로 찐 버퍼 설정해주는 함수 */
/* k: 확장된 키의 밸류의 인덱스를 올리기위한 변수 */
char *ft_set_buff(t_cmd *cmd, t_arvl *crr, int idx, char **env)
{
    int quote;
    int i;
    int j;
    int k;
    char *buff;
        cmd = crr->content;
        i = 0;
        while (cmd->args[i])
        {
            j = 0;
            k = 0;
            while (cmd->args[i][j])
            {
                if (cmd->args[i][j] == quote)
                    k++;
                else if (quote == 0 && (cmd->args[i][j] == '\'' || cmd->args[i][j] == '\"'))
                    k++;
                else if (quote == '\"' && cmd->args[i][j] == '\\' && cmd->args[i][j + 1] )
                    k++;
                else if (quote == 0 && cmd->args[i][j] == '\\' && cmd->args[i][j + 1])
                    k++;
                else if (quote != '\'' && cmd->args[i][j] == '$' && cmd->args[i][j + 1])
				{
                    k = env_size(env, find_env(cmd->args[i], &j), k);
				}
                else
                {
                    k++;
                }
                j++;
            }
            i++;
        }
	printf("ft_set_buff()k:%d\n", k);
    buff = (char *)malloc((k + 1) * (sizeof(char)));
	buff[k] = '\0';
    return (buff);
}
/* 구분자 등 일차적인 파싱을 끝내고, 환경변수 확장 해줌.(이미 만든 cmd->args를) */
void parsing_second(t_arvl *node, char **env)
{
    t_arvl *crr;
    t_cmd *cmd;
    int i;
    char *buff;
    int j;
    int quote;
    int k = 0;
    int idx = -1;
    cmd = NULL;
    crr = node;

    while (crr != NULL)
    {
        cmd = crr->content;
        quote = 0;
        i = 0;
        while (cmd->args[i])
        {
            buff = ft_set_buff(cmd, crr, idx, env);
            j = 0;
            k = 0;
            while (cmd->args[i][j])
            {
//여기서 args찍어보면 $USER aa 일 경우 args : $USER, args : aa 이렇게 나오는데 환경변수 확장하고 그 뒤에 aa 까지 while문 돌아서 buff에 넣어줌
				//parsing second 들어오기 전에 결과 출력해보면 이상없어
                if (cmd->args[i][j] == quote)
                    quote = 0;
                else if (quote == 0 && (cmd->args[i][j] == '\'' || cmd->args[i][j] == '\"'))
                    quote = cmd->args[i][j];
                else if (quote == '\"' && cmd->args[i][j] == '\\' && cmd->args[i][j + 1] )
                    buff[k++] = cmd->args[i][++j];
                else if (quote == 0 && cmd->args[i][j] == '\\' && cmd->args[i][j + 1])
                    buff[k++] = cmd->args[i][j];
//$USER aa , $USER | "$USER" , $USER ; $USER 등 이런거 처리
                else if (quote == 0 && ((cmd->args[i][j] == '|') || cmd->args[i][j] == '>') || (cmd->args[i][j] == '<') || \
							(cmd->args[i][j] == ';'))
				{
					break;
				}
                else if (quote != '\'' && cmd->args[i][j] == '$' && cmd->args[i][j + 1])
{
                    check_split(&k, set_env_to_buf(env, find_env(cmd->args[i], &j), buff), &idx, quote); 
					//여기도
					if (quote == 0)
						j--;
				}
                else
                {
                    buff[k] = cmd->args[i][j];
                    k++;
                }
                j++;
            }
			buff[k] = '\0';
            cmd->args[i] = ft_strdup(buff);
            i++;
            free(buff);
			buff = NULL;
        }
        crr = crr->next;
    }
}

void print_nodes_to_head(t_arvl *head)
{
    t_arvl *current = head;
    int node_num = 1;
    while (current != NULL)
    {
        t_cmd *cmd = (t_cmd *)current->content;
        printf("Node %d:", node_num);
        if (cmd != NULL) 
        {
            for (int i = 0; cmd->args[i] != NULL; i++)
            {
                printf("\targs[%d] : %s ", i, cmd->args[i]);
            }
            printf("\nflag : %d\n", cmd->flag);
        }
        current = current->next;
        node_num++;
    }
}


void	parsing(t_info *info, char *line, char **env)
{
	char *cmd;
	cmd = ft_strtrim(line, " ");
	parsing_init(&info->head, info, line);
	while (cmd[info->i])
	{
		write(1, &cmd[info->i], 1);
		write(1, "  ", 2);
		parsing_check(cmd, info);
		info->i++;
		if (cmd[info->i] == '\0')
			push_args(info, line);
	}
	//info->buff[info->i] = '\0'; -> 이거랑
	// info->buff = ft_strtrim(info->buff, " "); -> 이거 마지막에 논리구조 확인해보고 뺴도 되는지 체크하기
	// if (*(info->buff))
	// 	push_args(info, line);
	if (info->quote != 0)
	{
		printf("fuck\n");
		exit(0);
	}
	/* print parsing check args */
	if (info->args_i)
		ft_lstadd_back(&info->head, ft_lstnew(info->content));
	print_nodes_to_head(info->head); //result
	printf("------------parsing check done--------------\n");
	parsing_second(info->head, env);
	print_nodes_to_head(info->head); //result
}