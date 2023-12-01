/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilko <ilko@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 19:30:26 by ilko              #+#    #+#             */
/*   Updated: 2023/12/01 16:06:41 by ilko             ###   ########.fr       */
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

/* parent, child, heredoc */
# define CHILD 0
# define PARENT 1
# define HEREDOC 2

/* pasrse line or exit args success, fail */
# define SUCCESS 0
# define FAIL 1

/* index in parsing */
# define I 0
# define K 1

/* child minishell pid */

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
	int		prev_flag;
	char	quote;
	char 	*buff;
	int		parsing_failed;
	t_arvl	*head;
	t_cmd	*content;
}	t_info;

typedef struct s_redi
{
	int		flag;
	char	*file_n;
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
	int		simple_cmd_flag;

	char	**all_path;
	char	*cur_cmd_path;
	
	int		pipe_fail_flag;
	int		pre_fd[2];
	int		next_fd[2];
	int		in_out_fd[2];
}	t_pipe;

typedef struct	s_data
{
	t_envl		*envl;
	char		**envp;
	char		*pwd;//
	char		**history;//

	int 		master_flag;
	t_arvl		*arvl;
	t_cmd_node	*cmd_node_head;
	t_cmd_node	*cmd_node_last;
	int			node_open_flag;
	int			args_i;
	int			pre_flag;
	t_pipe		*cur_pipe;

	int			cur_pid;
}	t_data;

/* parsing.c */
void	set_quote(t_info *info, char quot, char buffer);
char	*ft_strtok(char *str, char sepa);
int		check_sepa(char c);
char	*get_pre_sepa_str(char *input, int sepa_idx);
int		count_token(char *input);
char	*get_args_one_size(char *line, t_info *info);
void	push_args(t_info *info, char *line);
void	set_content(t_info *info, char *line, t_arvl **node, int flag);
char	*ft_substr(char *s, unsigned int start, size_t len);
char	*ft_strtrim(char *s1, char *set);
void	parsing_check(char *line, t_info *info);
char	*make_buff(int k);
void	make_first_init(t_info *info, char *line);
int		ft_isalnum(int c);
char	*find_env(char *str, int *j);
size_t	ft_strlcat(char *dst, char *src, size_t dstsize);
int		check_unset(char *str, char *envv);
int		set_env_to_buf(char **envv, char *env, char *buf);
void	check_split(int *k, int z, int *idx, char quote);
void	move_env_size(char **envv, char *env, int *k);
char	*set_buff(char *args_line, char **env);
void	parsing_second(t_arvl *node, char **env);
void	print_nodes_to_head(t_arvl *head);
void	parsing(t_info *info, char *line, char **env);
char	*word_parsing(char **args, int *idx, char **env, char *buff);
char	*ft_itoa(int nbr);
size_t	ft_strlcat(char *dst, char *src, size_t dstsize);
char	*ft_substr(char *s, unsigned int start, size_t len);
void	end_of_line(t_info *info, char *line);
void	init_word_parsing(int *quote, int i_k[2]);
char	*res_dup(char **args, char *buff, int k, int *idx);
void	init_set_buff(int *i, int *k);
void	expand_exit_code(char **buff, int *k, int *i);

/* ./execute_src/execute.c */
void	exe_data(t_data *data, char *root_file_name);
void	wait_parent(t_data *data, t_pipe *pipe_data);


/* ./builtin_src/buitin_func.c */
int		if_buitin_func(t_data *data, char **arvs);
/* 				cd_func.c */

void	set_pwd_env(t_data *data, char *cwd_temp);
void	cd_exe(t_data *data, char **arvs);

/* 				exit_func.c */
void	exit_exe(t_data *data, char **arvs);

/* 				export_func.c */
int		check_key(char *str, int unset_flag);
void	export_exe(t_data *data, char **arvs);
t_envl	*find_key(t_data *data, char *key);
void	print_all_export(t_data *data);

/* 				env_func.c */
void	env_exe(t_data *data, char **arvs);
int		find_index(char *str, char c);
void	modify_env(t_data *data, char *key, char *value);
void	add_env(t_data *data, char *key, char *value);
char	*get_env_value(t_data *data, char *key);

/* 				echo_func.c */
void	echo_exe(t_data *data, char **arvs);
/* 				unset_func.c*/
void	unset_exe(t_data *data, char **arvs);
/* 				pwd_func.c*/
void	pwd_exe(t_data *data, char **arvs);

/* util.src/pipe_func.c */
void	set_pipe(t_data *data, t_pipe *pip);
int		cnt_pipe(t_cmd_node *head);
int		next_if_pipe_fail(t_pipe *pipe_data, t_cmd_node **cur);
void	set_pipe_child(t_pipe *pipe_data);


/*			/remake_func.c */
void	remake_arvl(t_info *info, t_data *data);
void	set_data_args(t_data *data, t_arvl *cur, int pre_flag, int par_i);

/* 			/redirect_func.c */
void	redirect_file(char **envp, t_redi *redi, t_pipe *pipe_data);
int		redirect_file_out(int flag, char *file_n);
int		redirect_file_in(char **envp, int flag, char *file_n, int *heredoc_f);

/*			/here_doc.c */
char	*res_dup_one(char *args, char *buff, int k);
char	*word_parsing_splitting(char *args, char **env, char *buff);
char	*parsing_second_args_tt(char *args, char **env);
void	here_doc(char **envp, char *limiter, int here_doc_temp_fd);


/*			/list_func.c */
t_envl	*make_env_node(t_data *data, char *key, char *value);
t_arvl	*ft_lstnew(void *content);
t_arvl	*ft_lstlast(t_arvl *lst);
void	ft_lstadd_back(t_arvl **lst, t_arvl *new);
int		get_lstsize(t_envl *cur);

/*			list_func2.c*/
void	clear_t_avrl(t_arvl **head);
void	clear_t_cmd_node(t_cmd_node **head);
void	clear_t_envl_node(t_envl **head);
t_redi	*new_redi_last_node(t_redi **head);
t_cmd_node	*new_cmd_last_node(t_cmd_node **head);

/* 			/init_func.c */
void	init_envl(t_data *data, char **envp, char *rootfile);
void	every_init(t_info *info, t_data *data);
void	envp_to_envl(t_data *data, char **envp, char *rootfile);
void	update_envp(t_data *data, t_envl *cur);
void	init_pipe(t_data *data, t_pipe *pipe_data);

/* 			/signal_func.c */
void	set_signal(int flag);
void	parent_sigint_handler(int signum);
void	child_sigint_handler(int signum);
void	here_doc_sigterm_handler(int signum);

/*			/path_func.c */
char	**get_all_path(char **envp);
char	*find_command(char *cmd, char **all_path);



/*			/free_func.c */
void	free_double(char ***str);
void	free_single(void **p);
void	free_every(t_data *data, t_info *info, char **line);
void	close_all_fd(t_pipe *pipe_data);


//구조체, 또는 노드 전체, 또는 노드 하나 프리하는 함수

/* ./str_src/str_func1.c */
char	**ft_split(char *s, char c);

/* ./str_src/str_func2.c */
int		ft_strlen(char *str);
int		ft_strcmp(char *s1, char *s2);
char	*ft_strdup(char *s1);
char	*ft_strndup(char *s1, int len);
char	*ft_strchr(char *s, int c);

/* ./str_src/str_func3.c */
char	*ft_strjoin(char *s1, char *s2);
char	*ft_strtrim(char *s1, char *set);
char	*ft_strcpy(char *dest, char *src);
void	*ft_calloc(size_t count, size_t size);
int		ft_strncmp(char *s1, char *s2, int n);

/* ./str_src/str_func4.c */
char	*ft_strtok(char *str, char sepa);

/* ./str_src/str_func5.c */
unsigned char	ft_atous_minishell(char *str, int *error);
int		ft_atoi(char *str);




/* ./error_done_src/exit_error.c */
void	exit_error(char *message, char *reason, int exit_code);
void	str_error(char *message, char *reason);
int		redi_perror(char *infile_name);



#endif