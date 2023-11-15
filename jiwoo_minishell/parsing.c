#include "minishell.h"

extern int exit_code;
//	printf("env_size() envv[i]:%s\n", envv[i]); <- 이거 인자로 넣으면 세그폴트 왜?
int	node_cnt = 1;

char *ft_itoa(int nbr) 
{
	if(nbr == -2147483648)
		return("-2147483648\0");
	int n = nbr;
	int len = 0;
	if (nbr <= 0)
	{
		len++;
    	}
	while (n) 
	{
		n /= 10;
		len++;
	}
	char *result = (char *)malloc(sizeof(char) * (len + 1));
	if (result == NULL) 
		return NULL;
	result[len] = '\0';
	if (nbr == 0)
	{
		result[0] = '0';
		return(result);
	}
	if (nbr < 0) 
	{
		result[0] = '-';
		nbr = -nbr;
	}
	while (nbr) 
	{
		result[--len] = nbr % 10 + '0';
		nbr /= 10;
	}
	return result;
}

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

//널문자는 체크 안하는걸로 수정함.
int	check_sepa(char c)
{
	if (c == '|' || c == ';' || c == '>' || c == '<' || c == '\0')
		return (1);
	return (0);
}
char	*get_pre_sepa_str(char *input, int sepa_idx)
{
	char	*res;
	int		i;

	res = ft_calloc(sepa_idx + 1, sizeof(char));
	i = 0;
	while (i < sepa_idx)
	{
		res[i] = input[i];
		i++;
	}
	res[i] = '\0';
	return (res);
}

//파이프 등 구분자 전 문자열을 공백으로 나누고 그 개수를 리턴(각 노드의 args배열의 크기)
int		count_token(char *input)//이 함수 작성자가 이렇게 구현한 이유가 있을텐데 흠 ..
{
	int		count_token;
	int		sepa_idx;
	char	*p;

	// p = ft_calloc(ft_strlen(input) + 1, sizeof(char));
	// ft_strcpy(p, input);
	sepa_idx = 0;
	while (check_sepa(input[sepa_idx]) == 0)//check_sepa 널문자는 처리 안하려고 수정할라했는데 여기서 쓰이는구나 ...
		sepa_idx++;
	while (input[sepa_idx] != '\0' && input[sepa_idx] != '|' && input[sepa_idx] != ';' && \
			input[sepa_idx] != '>' && input[sepa_idx] != '<')
		sepa_idx++;
	// if (sepa_idx == 0)
	// 	exit_error("syntax error near unexpected token", NULL, 258);//이 에러로 핸들링 하면 좋은데 호출이 꽤 늦은 함수라 여기서 되는지는 일단 엑싯 박아놓고 테스트 해보자.
	p = get_pre_sepa_str(input, sepa_idx);//이 함수는 말록을 해줘야함(이 함수에서 말록)
	count_token = 1;
	if (ft_strtok(p, ' ') != NULL)//여기 strtok은 매번 말록함
	{
		while (ft_strtok(NULL, ' ') != NULL)
			count_token++;
	}
	free(p);
	return (count_token);
}

//버퍼 관련 calloc으로 널문자 박기.ls >> aa bb
char *get_args_one_size(char *line)
{
	int i;
	int j;
	char *res;
	int quot;

	i = 0;
	j = 0;
	quot = 0;
	while (line[i] && ((line[i] >= 0 && line[i] <= 32) || (line[i] == '|') || ( line[i] == ';') || \
			(line[i] == '>') || (line[i] == '<')))
	{
		i++;
	}
	while (line[i] && ((line[i] != ' ' || quot != 2) && (line[i] != '|') && ( line[i] != ';') && (line[i] != '>' && \
			(line[i] != '<'))))
		{
			if (line[i] == '\"')
			{
				printf("quot == %d\n", quot);
				quot++;
			}
			// printf("line[i]:%c\n", line[i]);
			i++;
			j++;
		}
	// res = (char *)malloc((j + 1) * sizeof(char));
	res = calloc(j + 1, sizeof(char));
	printf("get_args_one_size()j:%d\n", j);
	res[j] = '\0';
	printf("out get_args_one_size()\n");
	return (res);
}

void	ft_bzero(void *s, size_t n)
{
	size_t i;

	i = 0;
	while (i < n)
	{
		*(char*)(s + i) = '\0';
		i++;
	}
}
//현재 args를 넣되, 그 다음의 것의 공간을 만드는 것 까지함. 다음이 널문자면 만들지 말까? 아니면 나중에 원활한 free를 위해 냅둘까? -> 여기서 free할테니 안만들겠다.
//문제는 원래는 안쓰는거 일단 만들고 봤는데, 구조상 널 문자가아닌 구분자들은 여기에 안들어옴.
void	push_args(t_info *info, char *line)
{
	printf("in push_args()\n");
	if (*(info->buff) == 0)
		return ;
	// if (check_sepa(line[info->i]) == 0 )//여기가 힙 버퍼 오버플로우 원인. 마지막에 + 1에 NULL박았었음
	// {
	
		info->content->args[info->args_i] = ft_strdup(info->buff);//여기 args는 결국엔 한 노드(파이프 등 구분자로 나눠진)의 배열이니 args배열은 구분자있으면 매번 초기화(새로 사이즈 재고 말록, 0초기화)해야하지 않나?
		free_single((void *)&info->buff);//굳이 널 안박아줘도 되긴 하지만 ..bzero ㅇㅏㄴ슬거면 여여기  널 박고 해해보보자
		if (line[info->i + 1] != '\0')
		{
			info->buff = get_args_one_size(&line[info->i]);//여기가 다음꺼 새로 만드는 시점
		}
		if (check_sepa(line[info->i]) == 1)//오 ..시바 여긴 공백없이 구분자 바로 올 때. 널 문자일 때도 들어가야함
				info->content->args[info->args_i + 1] = NULL;
	// }
	// else
	// {
		//info->buff = NULL;
	// }
	(info->args_i)++;
	info->j = 0;
	ft_bzero(info->buff, ft_strlen(info->buff) + 1);
	printf("content->args[info->args_i] == %s\n\n", info->content->args[info->args_i - 1]);
}
//구분자 전에 공백이 있으면 이미 만들어져있었을 것이고.. 아니면 안만들어져있을것이고 .. 를 지우의 info->buff 체크해보는 방식으로 해결
void		set_content(t_info *info, char *line, t_arvl **node, int i)
{
	if (line[info->i] == '>' && line[info->i + 1] == '>' || line[info->i] == '<' && \
		line[info->i + 1] == '<')
		info->i++;
	info->content->flag = i;
	// printf("info->buff:%s,%d\n", info->buff, info->buff[0]);
	// if (check_sepa(line[info->i + 1]) == 1)
	if (*(info->buff) != 0)//구분자 앞에 공백이 있어씅면 이미 처리가 됐을테니 현재 args_i는 널이 박혀야하는 자리인듯 하다.
		push_args(info, line);
	else
		info->content->args[info->args_i] = NULL;//여기였다.
	// printf("line[info->i + 1]:%c\tline[info->i]:%ci:%d\n", line[info->i + 1], line[info->i], info->i);
		ft_lstadd_back(node, ft_lstnew(info->content));//아래 조건문에서 밖으로 뺌
	/*if ((info->content->args)[0] == 0 && info->content->flag <= 1)//여긴 뭐 하는곳?
		exit(0);
	else */if (line[info->i + 1] != '\0')
	{
		info->content = ft_calloc(1, sizeof(t_cmd));
		info->content->args = ft_calloc(count_token(line + info->i + 1) + 1, sizeof(char *));

		info->content->flag = 0;	
	}
	info->args_i = 0;
	// while (line[info->i] != ' ' && line[info->i + 1] != '\0')//구분자 끝나고 노드 넣고 공백 밀어주는 곳
	// 	info->i++;
	//free and init
}



char	*ft_substr(char *s, unsigned int start, size_t len)
{
	int		i;
	char	*res;

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
	return (res);
}


//1. last
//2. file 
//3. cat -e

void parsing_check(char *line, t_info *info)
{
	write(1, &line[info->i], 1);
	write(1, "  ", 2);
	//마지막을 여기서 체크. 밖에서 quote가 열려있으면 에러처리. 맨 위에서 하는게 위험할것같아서 아래에서 했더니 안되던거 올리니 되네... 검증 해야하는 함수
    if (line[info->i] == info->quote)
        set_quote(info, 0, line[info->i]);
    else if (info->quote == 0 && (line[info->i] == '\'' || line[info->i] == '\"'))
        set_quote(info, line[info->i], line[info->i]);
    else if (info->quote == 0 && line[info->i] == '|')
	{
        set_content(info, line, &info->head, PIPE);
	}
    else if (info->quote == 0 && line[info->i] == ' ')
	{
	    push_args(info, line);
	} 
    else if (info->quote == 0 && line[info->i] == '>' && line[info->i + 1] != '>')
        set_content(info, line, &info->head, SIN_REDI_R);
    else if (info->quote == 0 && line[info->i] == '>' && line[info->i] == '>')
        set_content(info, line, &info->head, DOUB_REDI_R);
    else if (info->quote == 0 && line[info->i] == '<' && line[info->i + 1] != '<')
        set_content(info, line, &info->head, SIN_REDI_L);
    else if (info->quote == 0 && line[info->i] == '<' && line[info->i + 1] == '<')
        set_content(info, line, &info->head, DOUB_REDI_L);
    else if (info->quote == '\"' && line[info->i] == '\\')//너무 잘잘되되면  냅냅두고 ㅇ뭔가 따옴표 이이상상하하면 날려버리기
    {
        info->buff[info->j++] = line[info->i];
        info->i++;
        info->buff[info->j++] = line[info->i];
    }
    else
	{
        info->buff[info->j++] = line[info->i];
	}
	printf("info->args_i:%d\n", info->args_i);
	if (line[info->i + 1] == '\0')//마지막 넣어주기  문제되면 *(info->buff) != 0 &&
	{
		push_args(info, line);
		ft_lstadd_back(&info->head, ft_lstnew(info->content));
	}
}


void make_first_init(t_info *info, char *line)
{
	info->args_i = 0;
	info->i = 0;
	info->j = 0;
	info->quote = 0;
	info->head = NULL;
	info->buff = get_args_one_size(line);
	info->content = (t_cmd *)malloc(sizeof(t_cmd));
	int count = count_token(line);
	info->content->args = ft_calloc(count, sizeof(char *) * (count + 1));
	printf("return val count_token:%d\n", count);
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
char	*find_env(char *str, int *j)
{
	char	*res;
	int		i;

	(*j)++;
	i = *j;
	while (str[i] && str[i] != '$' && ft_isalnum(str[i]))
		i++;
	i--;
	res = ft_strndup(str + *j, i - *j + 1);
	*j = i;
	printf("in find env res:%s\n", res);
	return (res);
	// return (ft_strdup(str + 1));

}
// char	*find_exit_code(int *j)
// {
// 	*j += 1;
// 	return (ft_itoa(exit_code));
// }


size_t  ft_strlcat(char *dst, char *src, size_t dstsize)
{
        size_t  i;
        size_t  dst_len;
        size_t  src_len;

        src_len = ft_strlen(src);
        if (dstsize == 0)
                return (src_len);
        dst_len = ft_strlen(dst);
        if (dst_len + 1 > dstsize)
                return (src_len + dstsize);
        i = 0;
        while (dst_len + i < dstsize - 1 && src[i])
        {
			// printf("strlcat()dst:%c, src:%c\n", dst[dst_len + i], src[i]);
                dst[dst_len + i] = src[i];
                i++;
        }
        dst[dst_len + i] = '\0';
        return (src_len + dst_len);
}


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

	while (envv[++i])
	{
		if (check_unset(env, envv[i]))
		{
			printf("set_env_to_buf() env:%sbuf:%s\n", env, buf);
			/////
			ft_strlcat(buf, \
			envv[i] + ft_strlen(env) + 1, ft_strlen(envv[i]) + ft_strlen(buf));
			break ;
		}
	}
	printf("42tu48tu\n");
	free(env);
	return ((int)ft_strlen(buf));
}

void		check_split(int *k, int z, int *idx, char quote)
{
	*k = z;
	if (quote != '\"')
		*idx = 1;
	printf("fufufucsklnfl ========= %d\n", *idx);
}

/* key의 길이를 리턴 */ /* 리턴값은 키의 '=' 다음의 인덱스, str은 $를 제외한 키의 문자열. '='를 찾지 못하고 널문자 만나면 0리턴해서 확장 안되게 하자*/
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
void move_env_size(char **envv, char *env, int *k)
{
	int	i;
	int	env_len;

	i = 0;
	env_len = ft_strlen(env);
	while (envv[i])
	{
		if (ft_strncmp(envv[i], env, env_len) == 0)
		{
			if (envv[i][env_len] == '=')
			{
				*k += ft_strlen(envv[i] + env_len + 1);
				// printf("env_size()k:%dvalue:%s\n", *k, envv[i] + env_len + 1);
			}
			break ;
		}
		i++;
	}
	free(env);
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
				// write(1, &cmd->args[i][j], 1);
				// write(1, "  ", 2);
				// printf("1ft_set_buff()k:%d\n", k);
                if (cmd->args[i][j] == quote)
                    k++;
                else if (quote == 0 && (cmd->args[i][j] == '\'' || cmd->args[i][j] == '\"'))
                    k++;
                else if (quote == '\"' && cmd->args[i][j] == '\\' && cmd->args[i][j + 1] )
                    k++;
                else if (quote == 0 && cmd->args[i][j] == '\\' && cmd->args[i][j + 1])
                    k++;
                else if (quote != '\'' && cmd->args[i][j] == '$' && cmd->args[i][j + 1])//이 조건만 아니면 모두 k++하는거 아닌ㄴ가?
				{
					k--;
                    move_env_size(env, find_env(cmd->args[i], &j), &k);// <-여기 댕글링 포인터 처리하려면 줄수 나눠야해 <-여기 달러문자 인덱스 잘못돼서 잘못된 k값 넘겨줌.
					continue ;
				}
                else
                {
                    k++;
                }
                j++;
            }
            i++;
        }
    buff = (char *)malloc((k + 1) * (sizeof(char)));
	buff[k] = '\0';
    return (buff);
}

int get_exit_code_len(int exit_code)
{
	int len;
	int temp;

	if (exit_code == 0)
		return (1);
	temp = exit_code;
	len = 0;
	while(temp)
	{
		temp /= 10;
		len++;
	}
	printf("\n\n\naaaaaaaaaaaaa == %d\n", len);
	return(len);
}

char *set_buff(char *args_line, char **env)
{
    int quote;
    int i;
    int k;
    char *buff;

	i = 0;
	k = 0;
	printf("sagasgas ==== %s\n", args_line);
	while (args_line[i])
	{
		// write(1, &args_line[i], 1);
		// write(1, "  ", 2);
		// printf("1ft_set_buff()k:%d\n", k);
		if (args_line[i] == quote)
			k++;
		else if (quote == 0 && (args_line[i] == '\'' || args_line[i] == '\"'))
			k++;
		else if (quote == '\"' && args_line[i] == '\\' && args_line[i + 1])
			k++;
		else if (quote == 0 && args_line[i] == '\\' && args_line[i + 1])
			k++;
		else if (quote != '\'' && args_line[i] == '$' && args_line[i + 1])//이 조건만 아니면 모두 k++하는거 아닌ㄴ가?
		{
			k--;
			if (args_line[i + 1] == '?')
			{
				//// 버퍼 크기
				i++;
				k += get_exit_code_len(exit_code);
			}
			else
			{
				move_env_size(env, find_env(args_line, &i), &k);// <-여기 댕글링 포인터 처리하려면 줄수 나눠야해 <-여기 달러문자 인덱스 잘못돼서 잘못된 k값 넘겨줌.
				continue ;
			}
		}
		else
		{
			k++;
		}
	i++;
	}
	printf("k == %d\n", k);
    buff = (char *)malloc((k + 1) * (sizeof(char)));
	buff[k] = '\0';
    return (buff);
}

char		*word_parsing_splitting(char **args, int *idx, char **env, char *buff)
{
	int quote;
	int i;
	int k;
	char *res;

	i = 0;
	quote = 0;
	k = 0;
	while(args[0][i])
	{
		if (args[0][i] == quote)
            quote = 0;
        else if (quote == 0 && (args[0][i] == '\'' || args[0][i] == '\"'))
            quote = args[0][i];
        else if (quote == '\"' && args[0][i] == '\\' && args[0][i + 1] )
            buff[k++] = args[0][++i];
        else if (quote == 0 && args[0][i] == '\\' && args[0][i + 1])
            buff[k++] = args[0][i];
        else if (quote == 0 && ((args[0][i] == '|') || args[0][i] == '>') || (args[0][i] == '<') || \
					(args[0][i] == ';'))
		{
			break;
		}
        else if (quote != '\'' && args[0][i] == '$' && args[0][i + 1])
		{
			buff[k] = '\0';
			printf("235253523o\n");
			if (args[0][i + 1] == '?')
			{
				char *ppp = ft_itoa(exit_code);
				int zzz = 0;
				
				while (ppp[zzz])
				{
					buff[k] = ppp[zzz];
					k++;
					zzz++;
				}
				
				i++;
				free_single((void **)&ppp);
			}
			else
			{
            	check_split(&k, set_env_to_buf(env, find_env(args[0], &i), buff), idx, quote);
			}
		}
        else
        {
        	buff[k] = args[0][i];
            	k++;
        }
	
		i++;
	}
	printf("buvuubvuv -== %s\n", buff);
		buff[k] = '\0';

		printf("buvuubvuv -== %s\n", buff);
		printf("235253523o\n");
		printf("i == %d\n", i);
		printf("buffggggggg= %s\n", buff);
        res = ft_strdup(buff);
        free(buff);
		buff = NULL;
		return(res);
}

char		*word_parsing(char **args, int *idx, char **env, char *buff)
{
	int quote;
	int i;
	int k;
	char *res;

	i = 0;
	quote = 0;
	k = 0;

	while(args[*idx][i])
	{
		printf("zzzz == %c\n",args[*idx][i]);
		if (args[*idx][i] == quote)
            quote = 0;
        else if (quote == 0 && (args[*idx][i] == '\'' || args[*idx][i] == '\"'))
            quote = args[*idx][i];
        else if (quote == '\"' && args[*idx][i] == '\\' && args[*idx][i + 1] )
            buff[k++] = args[*idx][++i];
        else if (quote == 0 && args[*idx][i] == '\\' && args[*idx][i + 1])
            buff[k++] = args[*idx][i];
        else if (quote == 0 && ((args[*idx][i] == '|') || args[*idx][i] == '>') || (args[*idx][i] == '<') || \
					(args[*idx][i] == ';'))
		{
			break;
		}
        else if (quote != '\'' && args[*idx][i] == '$' && args[*idx][i + 1])
		{
			
			// buff[k] = '\0';
			if (args[*idx][i + 1] == '?')
			{
				char *ppp = ft_itoa(exit_code);
				int zzz = 0;
				while (ppp[zzz])
				{
					buff[k] = ppp[zzz];
					k++;
					zzz++;
				}
				i++;
				free_single((void **)&ppp);
			}
			else
			{
				printf("ddddd\n");
            	k += set_env_to_buf(env, find_env(args[*idx], &i), buff);
			}
		}
        else
        {
        	buff[k] = args[*idx][i];
            	k++;
        }
		printf("jjjjj\n");
		i++;
	}
	printf("iiiii\n");
		buff[k] = '\0';
        res = ft_strdup(buff);
        free(buff);
		buff = NULL;
		return(res);
}
int		double_str_len(char **str)
{
	int idx;

	idx = 0;
	while (str[idx])
		idx++;
	printf("str[idx] == %d\n", idx);
	return (idx);
}

char		**parsing_second_args(char **args, char **env)
{
	char *buff;
	int i = 0;
	int idx = 0;
	char *args_temp;

	//// 커맨드가 하나일 때 ex) ls, ls -al, a="ls -al" -> $a
	if (double_str_len(args) == 1)
	{
		buff = set_buff(args[i], env);
		args[0] = word_parsing_splitting(args, &idx, env, buff);
		if (idx== 1)
		{
			printf("jisoo = %s\n", args[0]);
			args_temp = args[0];
			args = ft_split(args_temp, ' ');
			free(args_temp);
		}
	}
	///// 그 이외의 것들 ls | cat 이런거
	else
	{
		while (args[idx])
		{
			printf("jiwoooo = %s\n", args[idx]);
			buff = set_buff(args[idx], env);
			args[idx] = word_parsing(args, &idx, env, buff);
			printf("idx == %s\n", args[idx]);
			buff = NULL;
			printf("99\n");
			idx++;
		}
	}
	return(args);
}

/* 구분자 등 일차적인 파싱을 끝내고, 환경변수 확장 해줌.(이미 만든 cmd->args를) */
void parsing_second(t_arvl *node, char **env)
{
	printf("in parsing_second()\n");
    t_arvl *crr; // t_list
    t_cmd *cmd;
    
	crr = node;
	while (crr != NULL)
	{
		cmd = (t_cmd *)(crr->content);
		printf("cmd->args[0] = %s\n", cmd->args[0]);
		printf("cmd->args[0] = %s\n", cmd->args[1]);
		cmd->args = parsing_second_args(cmd->args, env);
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
        printf("Node %d :\n", node_num);
        if (cmd != NULL) 
        {
            for (int i = 0; cmd->args[i] != NULL; i++)
            {
                printf("  args : %s\n", cmd->args[i]);
            }
            printf("  flag : %d\n\n", cmd->flag);
        }
        current = current->next;
        node_num++;
    }
}
int check_line_error(char *line, int i, int flag)
{
	if (flag == 2)
	{
		i++;
		i++;
	}
	if (flag == 1)
		i++;
	while (line[i] == ' ')
		i++;
	if (line[i] == '\0' || line[i] == '|' || line[i] == '<' || line[i] == '>')
	{
		printf("syntax error\n");
		return(0);
	}
	return(1);
}

int check_line(char *line, int i)
{
	if (line[i] == '<' && line[i + 1] == '<')
	{
		if (!check_line_error(line, i ,2))
			return(0);
	}
	else if (line[i] == '>')
	{
		if (!check_line_error(line, i ,1))
			return(0);
	}
	else if (line[i] == '<')
	{
		if (!check_line_error(line, i ,1))
			return(0);
	}
	else if (line[i] == '|')
	{
		if (!check_line_error(line, i ,1))
			return(0);
	}
	return(1);
}

int error_case(char *line)
{
	int i= 0;
	if (line[0] == '|')
	{
		printf("syntax error\n");
		return(0);
	}
	while(line[i])
	{
		if (line[i] == '>' && line[i + 1] == '>')
		{
			if (!check_line_error(line, i ,2))
				return(0);
		}
		else if (!check_line(line, i))
			return(0);
		i++;
	}
	return(1);
}

void	parsing(t_info *info, char *line, char **env)
{
	char *cmd;
	cmd = ft_strtrim(line, " ");
	if (cmd == NULL)
		return ;
	if (!(error_case(line)))
		exit(1);
	make_first_init(info, cmd);
	while (cmd[info->i])
	{
		// write(1, &cmd[info->i], 1);
		// write(1, "  ", 2);
		parsing_check(cmd, info);
		info->i++;
		// if (cmd[info->i] == '\0')
		// 	push_args(info, cmd);
	}
	if (info->quote != 0)
	{
		printf("fuck\n");
		exit(0);
	}
	// free_single((void *)&info->buff);
	// print_nodes_to_head(info->head); //result
	printf("------------parsing check done--------------\n");
	parsing_second(info->head, env);
	printf("\n\n%d----------\n",exit_code);
	print_nodes_to_head(info->head); //result
}//push args 첫번째에 널이 들어간다 왜지? 