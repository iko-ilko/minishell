/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_done.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilko <ilko@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 15:41:19 by ilko              #+#    #+#             */
/*   Updated: 2023/09/24 20:56:00 by ilko             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	free_multi(char **str2)
{
	int	i;

	if (str2 != NULL)
	{
		i = 0;
		while (str2[i])
			free(str2[i++]);
		free(str2);
	}
}

void	error(char *message, char *reason, int exit_code)
{
	write(2, "pipex: ", 7);
	write(2, reason, ft_strlen(reason));
	write(2, ": ", 2);
	write(2, message, ft_strlen(message));
	write(2, "\n", 1);
	exit(exit_code);
}

int	exit_parent(int last_pid, int fd[2])
{
	int	status;

	close(fd[0]);
	close(fd[1]);
	waitpid(last_pid, &status, 0);
	while (wait(NULL) != -1)
		;
	exit(WEXITSTATUS(status));
}
