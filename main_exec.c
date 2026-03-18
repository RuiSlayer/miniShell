/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgameiro <fgameiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 18:58:13 by slayer            #+#    #+#             */
/*   Updated: 2026/03/18 19:45:37 by fgameiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "incs/miniShell_exec.h"

int	cmd_eval(t_cmd *cmds, t_env **env)
{

	if (ft_strcmp(cmds->args[0], "exit") == 0)
		return (1);
	/* if (ft_strcmp(cmds->args[0], "echo") == 0)
		echo_cmd_redir(cmds->args[0]); */
	if (ft_strcmp(cmds->args[0], "pwd") == 0)
		pwd();
	if (ft_strcmp(cmds->args[0], "env") == 0)
		print_env(*env);
	if (ft_strcmp(cmds->args[0], "export") == 0)
		built_export(cmds, env);
	if (ft_strcmp(cmds->args[0], "cd") == 0)
		cd(cmds, env);
	if (ft_strcmp(cmds->args[0], "unset") == 0)
		unset(cmds, env);
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	char	*line;
	t_env	*env;
	t_token	*tokens;
	t_cmd	*cmds;

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
		if (*line == '\0')
		{
			free(line);
			continue ;
		}
		add_history(line);
		tokens = ft_tokenization_handler(line);
		free(line);
		if (!tokens)
			continue ;
		cmds = ft_parse(tokens);
		ft_clear_token_list(&tokens);
		if (!cmds)
			continue ;
		if (cmd_eval(cmds, &env))
			return (rl_clear_history(), free_env(env), ft_free_cmd_list(&cmds), 0);
		ft_free_cmd_list(&cmds);
	}
	return (0);
}
