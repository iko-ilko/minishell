/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwkim2 <jiwkim2@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 18:05:03 by jiwkim2           #+#    #+#             */
/*   Updated: 2023/09/16 19:29:41 by jiwkim2          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include <string.h>
# include <strings.h>
# include <unistd.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>

# define SEMICOLON_NONE 0
# define PIPE 1
# define SINGLE_REDIRECTION_RIGHT 2
# define DOUBLE_REDIRECTION_RIGHT 3
# define SINGLE_REDIRECTION_LEFT 4
# define DOUBLE_REDIRECTION_LEFT 5


typedef	struct	s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

typedef struct	s_cmd
{
	int		flag;
	char	**program;
}	t_cmd;

//p_i parsing index, j = buff index, i = line index
typedef struct	s_parsing
{
	int		p_i;
	int		i;
	int		j;
	int		token_count;
	char	quote;
	char 	*buff;
	// t_list	*head;
	t_cmd	*content;
}	t_parsing;


int		main(int argc, char **argv, char **env);
int		minishell(char **env);
void	prompt(void);

//libft
char	*ft_strdup(const char *s1);
char	*ft_strcpy(char *dest, char *src);
char	*ft_strchr(const char *s, int c);
void	*ft_calloc(size_t count, size_t size);
size_t	ft_strlen(const char *str);
t_list	*ft_lstnew(void *content);
void	ft_bzero(void *s, size_t n);
t_list	*ft_lstlast(t_list *lst);
void	ft_lstadd_back(t_list **lst, t_list *new);

#endif


// char		*word_parsing_splitting(char **prgm, int *idx,
// 									const char **envp, char *buf)
// {
// 	char	quote;
// 	int		j;
// 	int		i;

// 	init_word_parsing(&quote, &j, &i);
// 	printf("sss: %s\n", prgm[0]);
// 	while (prgm[0][++i])
// 		if (prgm[0][i] == quote)
// 			quote = 0;
// 		else if (quote == 0 && (prgm[0][i] == '\'' || prgm[0][i] == '\"'))
// 			quote = prgm[0][i];
// 		else if (quote == '\"' && prgm[0][i] == '\\' && prgm[0][i + 1] &&
// 				double_quote_escape(prgm[0][i + 1]))
// 			buf[j++] = prgm[0][++i];
// 		else if (quote == 0 && prgm[0][i] == '\\' && prgm[0][i + 1])
// 			buf[j++] = prgm[0][++i];
// 		else if (quote != '\'' && prgm[0][i] == '$' && prgm[0][i + 1])
// 			// if (prgm[0][i + 1] == '?' && (i += 2))
// 			// 	set_exit_status_to_buf(buf, &j, &i);
// 			// else
// 				check_split(&j, set_env_to_buf(envp,
// 						find_env(prgm[0], &i), buf), idx, quote);
// 		else
// 			buf[j++] = prgm[0][i];
// 	free(prgm[0]);
// 	return (ft_strdup(buf));
// }
