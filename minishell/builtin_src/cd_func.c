/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_func.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilko <ilko@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 15:06:41 by ilko              #+#    #+#             */
/*   Updated: 2023/12/01 15:10:01 by ilko             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

extern int	g_exit_code;

void	cd_home(t_data *data, char *error_str)
{
	char	*home_dir;

	home_dir = get_env_value(data, "HOME");
	if (home_dir == NULL)
	{
		if (home_dir == NULL || chdir(home_dir) == -1)
		{
			if (home_dir == NULL)
				str_error("HOME not set anywhere..", "cd");
			else
				perror(error_str);
			g_exit_code = 1;
		}
	}
	else
	{
		if (chdir(home_dir) == -1)
		{
			perror(error_str);
			g_exit_code = 1;
		}
	}
}

void	set_pwd_env(t_data *data, char *cwd_temp)
{
	char	*temp;

	temp = getcwd(NULL, 0);
	if (temp == NULL && cwd_temp == NULL)
	{
		str_error("getcwd failed", "cd");
		g_exit_code = 1;
		return ;
	}
	modify_env(data, ft_strdup("PWD"), ft_strdup(temp));
	modify_env(data, ft_strdup("OLDPWD"), ft_strdup(cwd_temp));
	free_single((void **)&temp);
}

void	cd_exe(t_data *data, char **arvs)
{
	char	*error_str;
	char	*cwd_temp;

	error_str = ft_strjoin("minishell: cd: ", arvs[1]);
	cwd_temp = getcwd(NULL, 0);
	if (arvs[1] == NULL || ft_strcmp(arvs[1], "~") == 0)
		cd_home(data, error_str);
	else if (chdir(arvs[1]) == -1)
	{
		perror(error_str);
		g_exit_code = 1;
	}
	set_pwd_env(data, cwd_temp);
	free_single((void *)&error_str);
	free_single((void *)&cwd_temp);
}
