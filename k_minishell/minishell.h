/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilko <ilko@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 19:30:26 by ilko              #+#    #+#             */
/*   Updated: 2023/10/01 23:55:18 by ilko             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>

typedef struct	s_envl
{
	char			*key;
	char			*value;
	struct s_envl	*next;
}	t_envl;


/* linkedlist */
typedef	struct	s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

/* command token */
typedef struct	s_cmd
{
	int		flag;
	char	**program;
}	t_cmd;

//p_i parsing index, j = buff index, i = line index
typedef struct	s_vars
{
	t_envl	*envl;
	char	*pwd;//
	char	**history;

	int		cur_pid;
	int		last_exit_code;
	
	int		p_i;
	int		i;
	int		j;
	int		token_count;
	char	quote;
	char 	*buff;
	// t_list	*head;
	t_cmd	*content;
}	t_vars;


/* init_func.c */
void	init_exe_data(t_vars *vars, char **envp);
void    envp_to_envl(t_vars *vars, char **envp);

/* ./builtin_src/buitin_func.c */
int		if_buitin_func(t_vars *vars, char **arvs);
/* 				cd_func.c */
void	cd_exe(t_vars *vars, char **arvs);
/* 				exit_func.c */
void	exit_exe(t_vars *vars, char **arvs);	
/* 				export_func.c */
void    export_exe(t_vars *vars, char **arvs);
void	add_env(t_vars *vars, char *key, char *value);
void	modify_env(t_vars *vars, char *key, char *value);
t_envl	*find_env(t_vars *vars, char *key);//파싱에서도 쓸 수 있게 노드를 반환
/* 				env_func.c */
void	env_exe(t_vars *vars, char **arvs);
/* 				echo_func.c */
void	echo_exe(t_vars *vars, char **arvs);
/* 				unset_func.c*/
void	unset_exe(t_vars *vars, char *key);
/* 				pwd_func.c*/
void	pwd_exe(t_vars *vars, char **arvs);
/* 				history.c */
void    save_history(t_vars *vars, char *line);

/* ./child_process/shell_child.c */
int if_more_shell(t_vars *vars, char **arv, char **temp, char **envp);
/* 				execute_child.c */


/* util.src/list_func.c */
// void	list_add_back(t_envl **envl, char *key, char *value);
t_envl	*make_env_node(t_vars *vars, char *key, char *value);




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
// int		str_check_space(char *str);
int		find_index(char *str, char c);


/* ./error_done_src/error.c */
void	error(char *message, char *reason, int exit_code);


#endif