/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slayer <slayer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 18:58:13 by slayer            #+#    #+#             */
/*   Updated: 2026/01/22 19:44:30 by slayer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniShell.h"

static void handle_sigint(int sig)
{
	(void)sig;
	write(STDOUT_FILENO, "\n", 1);  // async-signal-safe newline

	rl_on_new_line();               // move to a new, empty line
	rl_replace_line("", 0);         // clear current buffer
	rl_redisplay();                 // show prompt again
}
static void handle_sigquit(int sig)
{
	(void)sig;
	// At the interactive prompt, usually do nothing
	// You could also print a newline if you want:
	// write(STDOUT_FILENO, "Quit (ignored)\n", 15);
}

int	echo_cmd(char *line)
{
	printf("%s\n", line);
	return (0);
}

int	cmd_eval(char *line)
{
	char *p = line;

	while (*p == ' ' || *p == '\t')
		p++;
	if (strcmp(line, "exit") == 0)
		return (1);
	if (strcmp(line, "echo") == 0)
		echo_cmd(p);
	return (0);
}

int main(void)
{
	char *line;
	struct sigaction sa;

	sa.sa_handler = handle_sigint;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sa, NULL);

	// now use handle_sigquit so it is not unused
	sa.sa_handler = handle_sigquit;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGQUIT, &sa, NULL);

	while (1) {
		line = readline("prompt> ");
		if (line == NULL) {
			write(STDOUT_FILENO, "\n", 1);
			return 0;
		}
		if (cmd_eval(line))
			return (free(line), 0);
		if (*line)
			add_history(line);
		free(line);
	}
}
