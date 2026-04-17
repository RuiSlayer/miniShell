/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handle.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slayer <slayer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/11 15:24:21 by slayer            #+#    #+#             */
/*   Updated: 2026/04/17 20:33:56 by slayer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/miniShell_exec.h"

static void	handle_sigint(int sig)
{
	(void)sig;
	if (g_signal == HEREDOC_RUNNING)
	{
		write(STDOUT_FILENO, "^C", 3);
		g_signal = SIGINT;
		rl_done = 1;
		return ;
	}
	if (g_signal == CHILD_RUNNING)
	{
		write(STDOUT_FILENO, "\n", 1);
		g_signal = SIGINT;
		rl_done = 1;
		return ;
	}
	write(STDOUT_FILENO, "^C\n", 3);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	g_signal = SIGINT;
}

void	heredoc_signals(void)
{
	struct sigaction	sa;

	sa.sa_handler = handle_sigint;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGINT, &sa, NULL);
	sa.sa_handler = SIG_IGN;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGQUIT, &sa, NULL);
}

int	heredoc_event_hook(void)
{
	if (g_signal == SIGINT)
		rl_done = 1;
	return (0);
}

void	setup_signals(void)
{
	struct sigaction	sa;

	sa.sa_handler = handle_sigint;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sa, NULL);
	sa.sa_handler = SIG_IGN;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGQUIT, &sa, NULL);
}

void	child_signals(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}
