/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_func.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilko <ilko@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 15:11:00 by ilko              #+#    #+#             */
/*   Updated: 2023/12/01 15:34:44 by ilko             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

extern int	g_exit_code;

void	exit_exe(t_data *data, char **arvs)
{
	int	suc_flag;
	int	exit_code;

	if (data->cur_pipe->pipe_cnt == 0)
		write(2, "exit\n", 5);
	suc_flag = 0;
	exit_code = ft_atous_minishell(arvs[1], &suc_flag);
	if (arvs[1] != NULL && suc_flag == FAIL)
	{
		write(2, "minishell: exit: ", 17);
		write(2, arvs[1], ft_strlen(arvs[1]));
		write(2, ": numeric argument required\n", 28);
	}
	else if (arvs[1] != NULL && arvs[2] != NULL)
	{
		g_exit_code = 1;
		write(2, "minishell: exit: too many arguments\n", 36);
		return ;
	}
	free_double(&data->envp);
	exit(exit_code);
}
