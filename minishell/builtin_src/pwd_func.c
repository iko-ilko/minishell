/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_func.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilko <ilko@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 15:17:17 by ilko              #+#    #+#             */
/*   Updated: 2023/12/01 17:21:10 by ilko             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

extern int	g_exit_code;

void	pwd_exe(t_data *data)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (pwd != NULL)
	{
		write(data->cur_pipe->in_out_fd[1], pwd, ft_strlen(pwd));
		write(data->cur_pipe->in_out_fd[1], "\n", 1);
		free_single((void **)&pwd);
	}
	else
		str_error("getcwd failed", "pwd");
}
