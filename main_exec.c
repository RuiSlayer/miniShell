/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgameiro <fgameiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 18:58:13 by slayer            #+#    #+#             */
/*   Updated: 2026/03/25 00:25:53 by fgameiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "incs/miniShell_exec.h"

int	cmd_eval(t_shell *shell)
{

	if (ft_strcmp(shell->cmds->args[0], "exit") == 0)
		return (1);
	/* if (ft_strcmp(cmds->args[0], "echo") == 0)
		echo_cmd_redir(cmds->args[0]); */
	if (ft_strcmp(shell->cmds->args[0], "pwd") == 0)
		pwd();
	if (ft_strcmp(shell->cmds->args[0], "env") == 0)
		print_env(shell->env);
	if (ft_strcmp(shell->cmds->args[0], "export") == 0)
		built_export(shell->cmds, &shell->env);
	if (ft_strcmp(shell->cmds->args[0], "cd") == 0)
		cd(shell->cmds, &shell->env);
	if (ft_strcmp(shell->cmds->args[0], "unset") == 0)
		unset(shell->cmds, &shell->env);
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	t_shell		shell;
	t_token	*tokens;
	char		*line;

	(void)argc;
	(void)argv;
	shell.env = NULL;
	shell.cmds = NULL;
	shell.exit_status = 0;
	save_env(&shell.env, envp);
	setup_signals();
	while (1)
	{
		line = readline("prompt> ");
		if (line == NULL)
		{
			write(STDOUT_FILENO, "\n", 1);
			return (rl_clear_history(), free_env(shell.env), 0);
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
		shell.cmds = ft_parse(tokens);
		ft_clear_token_list(&tokens);
		if (!shell.cmds)
			continue ;
		ft_expand(&shell);
		if (cmd_eval(&shell))
			return (rl_clear_history(), free_env(shell.env), ft_free_cmd_list(&shell.cmds), shell.exit_status);
		ft_free_cmd_list(&shell.cmds);
	}
	return (shell.exit_status);
}
