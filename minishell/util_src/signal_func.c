/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_func.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilko <ilko@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 15:49:02 by ilko              #+#    #+#             */
/*   Updated: 2023/12/01 15:49:02 by ilko             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

extern int	g_exit_code;

void	set_signal(int flag)
{
	if (flag == PARENT)
	{
		rl_catch_signals = 0;
		signal(SIGINT, parent_sigint_handler);
		signal(SIGQUIT, SIG_IGN);
	}
	else if (flag == HEREDOC)
	{
		rl_catch_signals = 0;
		signal(SIGINT, here_doc_sigint_handler);
		signal(SIGQUIT, SIG_IGN);
		signal(SIGTERM, SIG_DFL);
	}
}

void	here_doc_sigint_handler(int signum)
{
	(void)signum;
	ioctl(STDIN_FILENO, TIOCSTI, "\04");
	rl_on_new_line();
	rl_replace_line("", 0);
	g_exit_code = 1;
}

void	parent_sigint_handler(int signum)
{
	(void)signum;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	g_exit_code = 1;
}
