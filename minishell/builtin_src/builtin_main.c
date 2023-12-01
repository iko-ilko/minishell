/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_main.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilko <ilko@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 15:06:22 by ilko              #+#    #+#             */
/*   Updated: 2023/12/01 15:06:30 by ilko             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	if_buitin_func(t_data *data, char **arvs)
{
	if (ft_strcmp(arvs[0], "cd") == 0)
		cd_exe(data, arvs);
	else if (ft_strcmp(arvs[0], "echo") == 0)
		echo_exe(data, arvs);
	else if (ft_strcmp(arvs[0], "pwd") == 0)
		pwd_exe(data);
	else if (ft_strcmp(arvs[0], "export") == 0)
		export_exe(data, arvs);
	else if (ft_strcmp(arvs[0], "unset") == 0)
		unset_exe(data, arvs);
	else if (ft_strcmp(arvs[0], "env") == 0)
		env_exe(data, arvs);
	else if (ft_strcmp(arvs[0], "exit") == 0)
		exit_exe(data, arvs);
	else
		return (0);
	return (1);
}
