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
	else if (flag == CHILD)
	{
		signal(SIGINT, child_sigint_handler);
		signal(SIGQUIT, SIG_IGN);
	}
	else if (flag == HEREDOC)
	{
		signal(SIGINT, parent_sigint_handler);
		signal(SIGQUIT, SIG_IGN);
		signal(SIGTERM, here_doc_sigterm_handler);
	}
}

void	here_doc_sigterm_handler(int signum)
{
	(void)signum;
	write(1, "here_doc_sigterm_handler\n", 26);
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
}

void	child_sigint_handler(int signum)
{
	(void)signum;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
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
