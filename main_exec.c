/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slayer <slayer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 18:58:13 by slayer            #+#    #+#             */
/*   Updated: 2026/03/31 03:52:31 by slayer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "incs/miniShell_exec.h"

char	*resolve_path(char *cmd, char **envp)
{
    // If cmd is already absolute or relative
    if (cmd[0] == '/' || cmd[0] == '.')
        return cmd;

    // Find PATH in envp
    char *path_env = NULL;
    for (int i = 0; envp[i]; i++) {
        if (ft_strncmp(envp[i], "PATH=", 5) == 0) {
            path_env = envp[i] + 5;
            break;
        }
    }
    if (!path_env) return NULL;

    // Try each directory in PATH
    char *dirs = ft_strdup(path_env);
    char *dir  = strtok(dirs, ":"); // need to create a auxiliar function
    while (dir) {
        char full[1024];
        snprintf(full, sizeof(full), "%s/%s", dir, cmd);
        if (access(full, X_OK) == 0)
            return strdup(full);
        dir = strtok(NULL, ":");
    }
    free(dirs);
    return NULL; // not found
}

int	external_cmds(t_shell *shell)
{
	pid_t pid;

	pid = fork();
	if (pid < 0)
		return (perror("fork"), 1);
	if (pid == 0)
	{
		// Child process
		char **envp = env_to_array(shell->env);
		char *path = resolve_path(shell->cmds->args[0], envp); // find binary in PATH
		if (!path || execve(path, shell->cmds->args, envp) == -1)
		{
			perror("execve");
			exit(EXIT_FAILURE);
		}
	} else {
		// Parent waits
		int status;
		waitpid(pid, &status, 0);
	}
	return (0);
}

int	cmd_eval(t_shell *shell)
{
	if (ft_strcmp(shell->cmds->args[0], "exit") == 0)
		return (1);
	else if (ft_strcmp(shell->cmds->args[0], "echo") == 0)
		echo(shell->cmds);
	else if (ft_strcmp(shell->cmds->args[0], "pwd") == 0)
		pwd();
	else if (ft_strcmp(shell->cmds->args[0], "env") == 0)
		print_env(shell->env);
	else if (ft_strcmp(shell->cmds->args[0], "export") == 0)
		built_export(shell->cmds, &shell->env);
	else if (ft_strcmp(shell->cmds->args[0], "cd") == 0)
		cd(shell->cmds, &shell->env);
	else if (ft_strcmp(shell->cmds->args[0], "unset") == 0)
		unset(shell->cmds, &shell->env);
	else
		external_cmds(shell);
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
