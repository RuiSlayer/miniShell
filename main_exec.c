/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgameiro <fgameiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 18:58:13 by slayer            #+#    #+#             */
/*   Updated: 2026/03/31 20:29:54 by fgameiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "incs/miniShell_exec.h"

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
		char *path = ft_find_path(shell->cmds->args[0], shell->env); // find binary in PATH
		
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

void	cmd_count(t_shell *shell)
{
	t_cmd	*cmd;
	int		i;

	i = 0;
	cmd = shell->cmds;
	while (cmd)
	{
		i++;
		cmd = cmd->next;
	}
	shell->cmd_count = i;
}

int	cmd_exec_loop(t_shell *shell)
{
	int     fd[2];
	int     prev_read = -1; // read-end carried from previous pipe
	pid_t   pids[shell->cmd_count];
	int     i = 0;
	int     status;

	while (shell->cmds)
	{
		if (shell->cmds->next)          // not the last command: create a pipe
		{
			if (pipe(fd) == -1)
				return (perror("pipe"), 1);
		}

		pids[i] = fork();
		if (pids[i] < 0)
			return (perror("fork"), 1);

		if (pids[i] == 0)               // ── child ──
		{
			if (prev_read != -1)        // wire previous pipe's read → stdin
			{
				dup2(prev_read, STDIN_FILENO);
				close(prev_read);
			}
			if (shell->cmds->next)      // wire this pipe's write → stdout
			{
				dup2(fd[1], STDOUT_FILENO);
				close(fd[1]);
				close(fd[0]);
			}
			cmd_eval(shell);
			perror("execve");
			exit(1);
		}

		// ── parent ──
		if (prev_read != -1)
			close(prev_read);           // done with previous read-end
		if (shell->cmds->next)
		{
			close(fd[1]);               // parent never writes
			prev_read = fd[0];          // carry read-end to next iteration
		}
		shell->cmds = shell->cmds->next;
		i++;
	}

	while (--i >= 0)                    // wait for ALL children after the loop
		waitpid(pids[i], &status, 0);

	return (WEXITSTATUS(status));
}

int	main(int argc, char **argv, char **envp)
{
	t_shell		shell;
	t_token		*tokens;
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
		/* if (cmd_eval(&shell))
			return (rl_clear_history(), free_env(shell.env), ft_free_cmd_list(&shell.cmds), shell.exit_status); */
		cmd_count(&shell);
		cmd_exec_loop(&shell);
		ft_free_cmd_list(&shell.cmds);
	}
	return (shell.exit_status);
}
