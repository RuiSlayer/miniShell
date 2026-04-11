/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handle.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgameiro <fgameiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/11 15:24:21 by slayer            #+#    #+#             */
/*   Updated: 2026/04/08 22:11:06 by fgameiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/miniShell_exec.h"

static void	handle_sigint(int sig)
{
	(void)sig;
	write(STDOUT_FILENO, "\n", 1);// async-signal-safe newline
	rl_on_new_line();// move to a new, empty line
	rl_replace_line("", 0);// clear current buffer
	rl_redisplay();// show prompt again
}

static void	handle_sigquit(int sig)
{
	(void)sig;
	// At the interactive prompt, usually do nothing
	// You could also print a newline if you want:
	// write(STDOUT_FILENO, "Quit (ignored)\n", 15);
}

void	setup_signals(void)
{
	struct sigaction	sa;

	sa.sa_handler = handle_sigint;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sa, NULL);
	sa.sa_handler = handle_sigquit;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGQUIT, &sa, NULL);
}
