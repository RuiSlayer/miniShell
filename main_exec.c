/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rucosta <rucosta@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 18:58:13 by slayer            #+#    #+#             */
/*   Updated: 2026/03/11 22:51:04 by rucosta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniShell_exec.h"

int	cmd_eval(char *line, t_env **env)
{
	char *p = line;
	char *tmp_unset[] = {"COLORFGBG", "two=2", NULL};
	/* char *tmp_export[] = {"two=2", NULL}; */
	char **args_unset = tmp_unset;
	/* char **args_export = tmp_export; */

	while (*p == ' ' || *p == '\t')
		p++;
	if (ft_strcmp(p, "exit") == 0)
		return (1);
	if (ft_strcmp(p, "echo") == 0)
		echo_cmd_redir(p);
	if (ft_strcmp(p, "pwd") == 0)
		pwd();
	if (ft_strcmp(p, "env") == 0)
		print_env(*env);
	if (ft_strcmp(p, "export") == 0)
		built_export(NULL, env);
	if (ft_strcmp(p, "cd") == 0)
		cd("..", env);
	if (ft_strcmp(p, "unset") == 0)
		unset(args_unset, env);
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	char	*line;
	t_env	*env;

	env = NULL;
	save_env(&env, envp);
	(void)argc;
	(void)argv;
	setup_signals();
	while (1)
	{
		line = readline("prompt> ");
		if (line == NULL)
		{
			write(STDOUT_FILENO, "\n", 1);
			return (rl_clear_history(), free_env(env), 0);
		}
		if (cmd_eval(line, &env))
			return (rl_clear_history(), free_env(env), free(line), 0);
		if (*line)
			add_history(line);
		free(line);
	}
	return (0);
}
