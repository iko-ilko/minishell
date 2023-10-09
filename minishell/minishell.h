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
# define PIPE 1
# define SI_REDI_R 2 // >
# define DOUB_REDI_R 3 // >> 
# define SI_REDI_L 4 // <
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
}	t_info;

typedef struct	s_data
{
	t_arvl	*arvl;
	t_envl	*envl;
	char	*pwd;//
	char	**history;

	int		cur_pid;
	int		last_exit_code;
}	t_data;




/* parsing.c */
void 	set_quote(t_info *info, char quot, char buffer);
char	*ft_strtok(char *str, char sepa);
int		count_token(char *input);
char 	*ft_size_check(char *line);
void	push_args(t_info *info, char *line);
void	set_content(t_info *info, char *line, t_arvl **node, int i);
void	put_args(t_info *info);
char	*ft_substr(char *s, unsigned int start, size_t len);
char	*ft_strtrim(char *s1, char *set);
void 	parsing_check(char *line, t_info *info);
void	*ft_memmove(void *dst, void *src, size_t len);
void	init(t_arvl **node, t_info *info, char *line);
int		ft_isalnum(int c);
char	*p_find_env(char *str, int *i);
size_t	ft_strlcat(char *dst, char *src, size_t dstsize);
int		check_unset(char *str, char *envv);
int		set_env_to_buf(char **envv, char *env, char *buf);
void	check_split(int *j, int z, int *idx, char quote);
int     check_unset_sub(char *str, char *envv);
int 	env_size(char **envv, char *env, int k);
char	*ft_set_buff(t_cmd *cmd, t_arvl *crr, int idx, char **env);
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
void	free_vars(t_data *data);
void	free_double(char ***str);
void	free_single(void **str);

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
void	 more_shell(t_data *data, char **arvs, char *root_file_name, char **envp);
/* 				execute_child.c */


/* util.src/list_func.c */
t_envl	*make_env_node(t_data *data, char *key, char *value);
t_arvl	*ft_lstnew(void *content);
t_arvl	*ft_lstlast(t_arvl *lst);
void	ft_lstadd_back(t_arvl **lst, t_arvl *new);

/* 			/init_func.c */
void	init_exe_data(t_data *data, char **envp, char *root_file);
void    envp_to_envl(t_data *data, char **envp, char *root_file);
/* 			/signal_func.c */
void    sigint_handler(int signum);
void    sigquit_handler(int signum);



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
void	ft_bzero(void *s, size_t n);
char	*ft_strcpy(char *dest, char *src);
void	*ft_calloc(size_t count, size_t size);



// int		str_check_space(char *str);
int		find_index(char *str, char c);


/* ./error_done_src/exit_error.c */
void	exit_error(char *message, char *reason, int exit_code);
void	str_error(char *message, char *reason);



#endif