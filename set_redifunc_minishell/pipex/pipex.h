/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilko <ilko@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 16:53:54 by ilko              #+#    #+#             */
/*   Updated: 2023/09/24 20:42:30 by ilko             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/wait.h>

# define BUFFER_SIZE 30

typedef struct s_back_node
{
	char	*str;
	int		len;
}	t_node;

typedef struct s_datas
{
	char	**arv;
	int		cmd_cnt;
	int		pipe_cnt;
	char	**envp;
	char	**all_path;
	int		pre_fd[2];
	int		next_fd[2];
	int		cur_pid;
	char	**cur_cmd_arvs;
	char	*cur_cmd_path;
	int		heredoc_f;
}	t_datas;

/* error_done.c */
void	error(char *message, char *reason, int exit_code);
int		exit_parent(int last_pid, int fd[2]);
void	free_multi(char **str2);

/* execute_child.c */
char	**get_all_path(char **envp);
char	*find_command(char *cmd, char **all_path);
void	first_child(t_datas *data, char *infile_name);
void	multiple_child(t_datas *data);
void	last_child(t_datas *data, char *outfile_name);

/* str_func.c */
int		ft_strlen(char *str);
char	*ft_strjoin(char *s1, char *s2);
int		ft_strncmp(char *s1, char *s2, int n);
char	*ft_strdup(char *s1);
char	*ft_strndup(char *s1, int len);

/* str_func2.c */
char	**ft_split(char *s, char c);

/* get_next_line.c */
char	*get_next_line(int fd);

#endif