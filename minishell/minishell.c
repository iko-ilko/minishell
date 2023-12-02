/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilko <ilko@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 15:50:05 by ilko              #+#    #+#             */
/*   Updated: 2023/12/02 17:40:12 by jiwkim2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_exit_code = 0;

void a()
{
    system("leaks minishell");
}

int	main(int arc, char **arv, char **envp)
{
	t_info	info;
	t_data	data;
	char	*line;

	if (arc != 1)
		exit_error("Too Many Argument", arv[1], 127);
	init_envl(&data, envp, arv[0]);
	while (1)
	{
		set_signal(PARENT);
		line = readline("minishell$ ");
		if (line == NULL)
			break ;
		every_init(&info, &data);
		parsing(&info, line, data.envp);
		if (info.parsing_failed == SUCCESS)
		{
			remake_arvl(&info, &data);
			exe_data(&data);
		}
		free_every(&data, &info, &line);
	}
	free_double(&data.envp);
	clear_t_envl_node(&data.envl);
	// atexit(a);
}
