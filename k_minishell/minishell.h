/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilko <ilko@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 19:30:26 by ilko              #+#    #+#             */
/*   Updated: 2023/09/27 20:20:03 by ilko             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <readline/readline.h>

/* ./builtin_src/cd_func.c */
void	cd_func(char **arvs);

/* ./str_src/str_func1.c */
char	**ft_split(char *s, char c);

/* ./str_src/str_func2.c */
int		ft_strlen(char *str);
int		ft_strcmp(char *s1, char *s2);

/* ./error_done_src/error.c */
void	error(char *message, char *reason, int exit_code);

#endif