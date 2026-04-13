/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handle.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slayer <slayer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/11 15:24:21 by slayer            #+#    #+#             */
/*   Updated: 2026/04/13 18:55:05 by slayer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/miniShell_exec.h"

static void	handle_sigint(int sig)
{
	(void)sig;
	write(STDOUT_FILENO, "\n", 1);
	if (g_signal == CHILD_RUNNING)  // child is running — just write newline
	{
		g_signal = SIGINT;          // let the parent know SIGINT happened
		return;                     // DON'T redisplay prompt here ← key fix
	}
	// shell is idle at prompt — redisplay
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	g_signal = SIGINT;
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
