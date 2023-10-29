/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilko <ilko@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 19:30:26 by ilko              #+#    #+#             */
/*   Updated: 2023/10/06 17:16:36 by ilko             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <signal.h>
# include <unistd.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>

/* export add, delete */
# define ADD 0
# define DEL 1

/* parsing flag */
# define SEMICOLON_NONE 0
# define PIPE 0
# define SIN_REDI_R 2 // >
# define DOUB_REDI_R 3 // >> 
# define SIN_REDI_L 4 // <
# define DOUB_REDI_L 5 // <<

# define REAl_DOUB_REDI_R 10
# define REAl_DOUB_REDI_L 11
# define REAL_SIN_REDI_R 12
# define REAL_SIN_REDI_L 13


/* env linkedlist */
typedef struct	s_envl
{
	char			*key;
	char			*value;
	struct s_envl	*next;
}	t_envl;


/* parsing arv linkedlist */
typedef	struct	s_arvl
{
	void			*content;
	struct s_arvl	*next;
}	t_arvl;

/* command token */
/* flag는 현재 구분자의 flag로 사용되고 있지만 후에 파일을 오픈한 fd값으로도 활용하려면 -1을 곱해줘서 음수로 만든다음 실행에서는 음수값을 양수로 바꿔서 활용 */
typedef struct	s_cmd
{
	int		flag;
	char	**args;
}	t_cmd;

//p_i parsing index, j = buff index, i = line index
typedef struct	s_info
{
	int		args_i;  // args배열의 인덱스
	int		i; // cmd의 인덱스. parsing함수에서 사용
	int		j; // buff의 인덱스. parsing_check함수에서 사용
	int		token_count;
	char	quote;
	char 	*buff;
	t_arvl	*head;
	t_cmd	*content;
	int		prev_flag;
}	t_info;

typedef struct	s_data
{
	t_arvl	*arvl;
	t_envl	*envl;
	char	**envp;
	char	*pwd;//
	char	**history;//
	int		cmd_cnt;

	int		cur_pid;
	int		last_exit_code;
}	t_data;




/* parsing.c */
void 	set_quote(t_info *info, char quot, char buffer);
char	*ft_strtok(char *str, char sepa);
int		check_sepa(char c);
char	*get_pre_sepa_str(char *input, int sepa_idx);
int		count_token(char *input);
char 	*get_args_one_size(char *line, int last_flag);
void	push_args(t_info *info, char *line);
void	set_content(t_info *info, char *line, t_arvl **node, int i);
char	*ft_substr(char *s, unsigned int start, size_t len);
char	*ft_strtrim(char *s1, char *set);
void 	parsing_check(char *line, t_info *info);
void	make_first_init(t_info *info, char *line);
int		ft_isalnum(int c);
char	*find_env(char *str, int *j);
size_t	ft_strlcat(char *dst, char *src, size_t dstsize);
int		check_unset(char *str, char *envv);
int		set_env_to_buf(char **envv, char *env, char *buf);
void	check_split(int *k, int z, int *idx, char quote);
int     check_unset_sub(char *str, char *envv);
void 	move_env_size(char **envv, char *env, int *k);
// char	*ft_set_buff(t_cmd *cmd, t_arvl *crr, int idx, char **env);
char	*set_buff(char *args_line, char **env);
void	parsing_second(t_arvl *node, char **env);
void	print_nodes_to_head(t_arvl *head);
void	parsing(t_info *info, char *line, char **env);



/* execute.c */
void	exe_data(t_data *data, char **envp, char *root_file_name);

/* ./builtin_src/buitin_func.c */
int		if_buitin_func(t_data *data, char **arvs);
/* 				cd_func.c */
void	cd_exe(t_data *data, char **arvs);
/* 				exit_func.c */
void	exit_exe(t_data *data, char **arvs);

/* 				export_func.c */
int		check_key(char *str, int unset_flag);
void    export_exe(t_data *data, char **arvs, int idx);

t_envl	*find_key(t_data *data, char *key);//파싱에서도 쓸 수 있게 노드를 반환
/* 				env_func.c */
void	env_exe(t_data *data, char **arvs);
int		find_index(char *str, char c);
void	modify_env(t_data *data, char *key, char *value);
void	add_env(t_data *data, char *key, char *value);

/* 				echo_func.c */
void	echo_exe(t_data *data, char **arvs);
/* 				unset_func.c*/
void	unset_exe(t_data *data, char **arvs, int idx);
/* 				pwd_func.c*/
void	pwd_exe(t_data *data, char **arvs);

/* ./child_process/shell_child.c */
void	more_shell(t_data *data, char **arvs, char **envp);
/* 				execute_child.c */


/* util.src/list_func.c */
t_envl	*make_env_node(t_data *data, char *key, char *value);
t_arvl	*ft_lstnew(void *content);
t_arvl	*ft_lstlast(t_arvl *lst);
void	ft_lstadd_back(t_arvl **lst, t_arvl *new);
int		get_lstsize(t_envl *cur);

/* 			/init_func.c */
void	init_exe_data(t_info *info, t_data *data, char **envp, char *rootfile);
void	envp_to_envl(t_data *data, char **envp, char *rootfile);
void	update_envp(t_data *data, t_envl *cur);
/* 			/signal_func.c */
void    sigint_handler(int signum);
void    sigquit_handler(int signum);
/*			/free_func.c */
void	free_vars(t_data *data);
void	free_double(char ***str);
void	free_single(void **str);
//구조체, 또는 노드 전체, 또는 노드 하나 프리하는 함수

/* ./str_src/str_func1.c */
char	**ft_split(char *s, char c);

/* ./str_src/str_func2.c */
int		ft_strlen(char *str);
int		ft_strcmp(char *s1, char *s2);
char	*ft_strdup(char *s1);
char	*ft_strndup(char *s1, int len);
char    *ft_strchr(char *s, int c);

/* ./str_src/str_func3.c */
char	*ft_strjoin(char *s1, char *s2);
char	*ft_strtrim(char *s1, char *set);
char	*ft_strcpy(char *dest, char *src);
void	*ft_calloc(size_t count, size_t size);
int		ft_strncmp(char *s1, char *s2, int n);

/* ./str_src/str_func4.c */
char	*ft_strtok(char *str, char sepa);




// int		str_check_space(char *str);
int		find_index(char *str, char c);


/* ./error_done_src/exit_error.c */
void	exit_error(char *message, char *reason, int exit_code);
void	str_error(char *message, char *reason);



#endif


