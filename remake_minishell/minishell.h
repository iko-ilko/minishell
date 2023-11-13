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
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>

/* export add, delete */
# define ADD 0
# define DEL 1

/* parsing flag */
# define NONE 0
# define PIPE 0
# define SIN_REDI_R 2 // >
# define DOUB_REDI_R 3 // >> 
# define SIN_REDI_L 4 // <
# define DOUB_REDI_L 5 // <<

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

/* redirection token. if NULL = none */



//p_i parsing index, j = buff index, i = line index
typedef struct	s_info
{
	int		args_i;  // args배열의 인덱스
	int		i; // cmd의 인덱스. parsing함수에서 사용
	int		j; // buff의 인덱스. parsing_check함수에서 사용
	int		token_count;
	int		prev_flag;
	char	quote;
	char 	*buff;
	t_arvl	*head;
	t_cmd	*content;
}	t_info;

typedef struct s_redi
{
	int		flag;
	// int		fd;
	char	*file_name;
	struct s_redi *next;
}	t_redi;

/* 실행에서 쓰이는 커맨드 리스트 */
typedef struct	s_cmd_node
{
	char				**args;
	//flag는 필요..없을듯?
	t_redi				*redi;
	struct s_cmd_node	*next;
}	t_cmd_node;

/* 매 라인 실행마다 초기화 해주는 파이프 */
typedef struct 	t_pipe
{
	int		cmd_idx;
	int		pipe_cnt;
	int		heredoc_f;

	char	**all_path;
	char	*cur_cmd_path;
	
	// inout을 배열로 둘까 그냥 변수로 둘까.. 
	//inoutfd를 file open한 fd와 stdio_back_fd의 값을 넘겨줘서 자식에서 dup2해주자.리다이렉션이 없으면 기본값 백업 fd로 넘겨주자.
	int		pre_fd[2];
	int		next_fd[2];

	int		in_out_fd[2];
	int		stdio_back_fd[2];
}	t_pipe;

typedef struct	s_data
{
	t_envl		*envl;
	char		**envp;
	char		*pwd;//
	char		**history;//

	t_arvl		*arvl;
	t_cmd_node	*cmd_node_head;
	t_cmd_node	*cmd_node_last;
	int			node_open_flag;
	int			args_i;
	int			pre_flag;
	// t_pipe	pipe_data; 함수 내에서 선언하자.

	int			cur_pid;
	int			last_exit_code;
}	t_data;

void	print_data_cmd(t_data *data);



/* parsing.c */
void 	set_quote(t_info *info, char quot, char buffer);
char	*ft_strtok(char *str, char sepa);
int		check_sepa(char c);
char	*get_pre_sepa_str(char *input, int sepa_idx);
int		count_token(char *input);
char 	*get_args_one_size(char *line);
void	push_args(t_info *info, char *line);
void	set_content(t_info *info, char *line, t_arvl **node, int flag);
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
void	exe_data(t_data *data, char *root_file_name);
void	here_doc(char *limiter, int here_doc_temp_fd);


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


/* util.src/pipe_func.c */
char	**get_all_path(char **envp);
char	*find_command(char *cmd, char **all_path);
void	set_pipe(t_pipe *pip);
int		cnt_pipe(t_cmd_node *head);
void	wait_parent(t_data *data, t_pipe *pipe_data);

/*			/remake_func.c */
void	remake_arvl(t_info *info, t_data *data);
void	set_data_args(t_data *data, t_arvl *cur, int pre_flag, int par_i);



/* 			/redirect_func.c */
void	redirect_file(t_redi *redi, t_pipe *pipe_data);
int		redirect_file_out(int flag, char *file_name);
int		redirect_file_in(int flag, char *file_name, int *heredoc_f);

/*			/list_func.c */
t_envl	*make_env_node(t_data *data, char *key, char *value);
t_arvl	*ft_lstnew(void *content);
t_arvl	*ft_lstlast(t_arvl *lst);
void	ft_lstadd_back(t_arvl **lst, t_arvl *new);
int		get_lstsize(t_envl *cur);

/* 			/init_func.c */
void	init_envl(t_data *data, char **envp, char *rootfile);
void	every_init(t_info *info, t_data *data);
void	envp_to_envl(t_data *data, char **envp, char *rootfile);
void	update_envp(t_data *data, t_envl *cur);
void	init_pipe(t_data *data, t_pipe *pipe_data);

/* 			/signal_func.c */
void    sigint_handler(int signum);
void    sigquit_handler(int signum);
/*			/free_func.c */
void	free_vars(t_data *data);
void	free_double(char ***str);
void	free_single(void **str);
void	free_every(t_data *data, t_info *info, char **line);

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
void	my_perror(char *infile_name);



#endif