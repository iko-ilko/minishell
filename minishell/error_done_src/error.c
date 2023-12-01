/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilko <ilko@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 15:35:15 by ilko              #+#    #+#             */
/*   Updated: 2023/12/01 15:35:15 by ilko             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

extern int	g_exit_code;

void	exit_error(char *message, char *reason, int exit_code)
{
	write(2, "minishell: ", 12);
	if (reason != NULL)
	{
		write(2, reason, ft_strlen(reason));
		write(2, ": ", 2);
	}
	write(2, message, ft_strlen(message));
	write(2, "\n", 1);
	exit(exit_code);
}

void	str_error(char *message, char *reason)
{
	write(2, "minishell: ", 12);
	if (reason != NULL)
	{
		write(2, reason, ft_strlen(reason));
		write(2, ": ", 2);
	}
	write(2, message, ft_strlen(message));
	write(2, "\n", 1);
	g_exit_code = 1;
}

int	redi_perror(char *infile_name)
{
	perror("minishell: ");
	return (-1);
}
