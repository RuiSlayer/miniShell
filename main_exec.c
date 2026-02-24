/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rucosta <rucosta@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 18:58:13 by slayer            #+#    #+#             */
/*   Updated: 2026/02/24 23:03:08 by rucosta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniShell_exec.h"

static void	handle_sigint(int sig)
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

int	cmd_eval(char *line, t_env *env)
{
	char *p = line;

	while (*p == ' ' || *p == '\t')
		p++;
	if (ft_strncmp(p, "exit", 4) == 0)
		return (1);
	if (ft_strncmp(p, "echo", 4) == 0)
		echo_cmd_redir(p);
	if (ft_strncmp(p, "pwd", 3) == 0)
		pwd();
	if (ft_strncmp(p, "env", 3) == 0)
		print_env(env);
	if (ft_strncmp(p, "export", 6) == 0)
		export(line, env);
	return (0);
}

int main(int argc, char **argv, char **envp)
{
	char				*line;
	struct sigaction	sa;
	t_env				*env;

	env = NULL;
	save_env(&env, envp);
	(void)argc;
	(void)argv;
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
			return (rl_clear_history(), 0);
		}
		if (cmd_eval(line, env))
			return (rl_clear_history(), free(line), 0);
		if (*line)
			add_history(line);
		free(line);
	}
	return (0);
}
