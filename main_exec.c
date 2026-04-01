/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgameiro <fgameiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 18:58:13 by slayer            #+#    #+#             */
/*   Updated: 2026/04/01 22:28:18 by fgameiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "incs/miniShell_exec.h"

int	external_cmds(t_shell *shell)
{
	char **envp = env_to_array(shell->env);
	char *path = ft_find_path(shell->cmds->args[0], shell->env); // find binary in PATH
	
	if (!path || execve(path, shell->cmds->args, envp) == -1)
	{
		perror("execve");
		exit(EXIT_FAILURE);
	}
	return (0);
}

int	run_builtin(t_shell *shell)
{
	if (ft_strcmp(shell->cmds->args[0], "exit") == 0)
		return (1);
	else if (ft_strcmp(shell->cmds->args[0], "echo") == 0)
		return (echo(shell->cmds));
	else if (ft_strcmp(shell->cmds->args[0], "pwd") == 0)
		return (pwd());
	else if (ft_strcmp(shell->cmds->args[0], "env") == 0)
		return (print_env(shell->env));
	else if (ft_strcmp(shell->cmds->args[0], "export") == 0)
		return (built_export(shell->cmds, &shell->env));
	else if (ft_strcmp(shell->cmds->args[0], "cd") == 0)
		return (cd(shell->cmds, &shell->env));
	else if (ft_strcmp(shell->cmds->args[0], "unset") == 0)
		return (unset(shell->cmds, &shell->env));
	return (0);
}

int	is_builtin(t_shell *shell)
{
	if (ft_strcmp(shell->cmds->args[0], "exit") == 0)
		return (1);
	else if (ft_strcmp(shell->cmds->args[0], "echo") == 0)
		return (1);
	else if (ft_strcmp(shell->cmds->args[0], "pwd") == 0)
		return (1);
	else if (ft_strcmp(shell->cmds->args[0], "env") == 0)
		return (1);
	else if (ft_strcmp(shell->cmds->args[0], "export") == 0)
		return (1);
	else if (ft_strcmp(shell->cmds->args[0], "cd") == 0)
		return (1);
	else if (ft_strcmp(shell->cmds->args[0], "unset") == 0)
		return (1);
	return (0);
}

int	apply_redirects(t_redir *redir)
{
	int fd;

	while (redir)
	{
		if (redir->type == R_IN)          // <
		{
			fd = open(redir->file, O_RDONLY);
			if (fd == -1) { perror(redir->file); return -1; }
			dup2(fd, STDIN_FILENO);
			close(fd);
		}
		else if (redir->type == R_OUT)    // >
		{
			fd = open(redir->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (fd == -1) { perror(redir->file); return -1; }
			dup2(fd, STDOUT_FILENO);
			close(fd);
		}
		else if (redir->type == R_APPEND) // >>
		{
			fd = open(redir->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
			if (fd == -1) { perror(redir->file); return -1; }
			dup2(fd, STDOUT_FILENO);
			close(fd);
		}
		else if (redir->type == R_HEREDOC)
		{
			dup2(redir->heredoc_fd, STDIN_FILENO);
			close(redir->heredoc_fd);
		}
		redir = redir->next;
	}
	return 0;
}

int    ft_setup_heredocs(t_cmd *cmds)
{
	t_cmd   *cmd;
	t_redir *redir;

	cmd = cmds;
	while (cmd)
	{
		redir = cmd->redirs;
		while (redir)
		{
			if (redir->type == R_HEREDOC)
			{
				if (apply_heredoc(redir) == -1)
					return (-1);
			}
			redir = redir->next;
		}
		cmd = cmd->next;
	}
	return (0);
}

int	apply_heredoc(t_redir *redir)
{
	int		pipefd[2];
	char	*line;
	
	if (pipe(pipefd) == -1)
	{
		perror("pipe");
		return (-1);
	}
	while (1)
	{
		line = readline("> ");
		if (!line || ft_strcmp(line, redir->file) == 0)
		{
			free(line);
			break ;
		}
		write(pipefd[1], line, ft_strlen(line));
		write(pipefd[1], "\n", 1);
		free(line);
	}
	close(pipefd[1]);
	redir->heredoc_fd = pipefd[0];
	return (0);
}

void	run_builtin_in_parent(t_cmd *cmd, t_shell *shell)
{
	int saved_in  = dup(STDIN_FILENO);
	int saved_out = dup(STDOUT_FILENO);

	// Aplica redirects temporariamente no pai
	if (apply_redirects(cmd->redirs) == -1)
	{
		dup2(saved_in,  STDIN_FILENO);
		dup2(saved_out, STDOUT_FILENO);
		close(saved_in); close(saved_out);
		return ;
	}

	shell->exit_status = run_builtin(shell);

	// Restaura stdin/stdout originais
	dup2(saved_in,  STDIN_FILENO);
	dup2(saved_out, STDOUT_FILENO);
	close(saved_in);
	close(saved_out);
}

void	child_process(t_cmd *cmd, int prev_fd, int pipe_fd[], t_shell *shell)
{
    // 1. Conecta ao pipe anterior (stdin)
    if (prev_fd != -1)
    {
        dup2(prev_fd, STDIN_FILENO);
        close(prev_fd);
    }
    // 2. Conecta ao pipe seguinte (stdout)
    if (cmd->next)
    {
        dup2(pipe_fd[1], STDOUT_FILENO);
        close(pipe_fd[0]);
        close(pipe_fd[1]);
    }
    // 3. Aplica redirects — em ordem, sobrescrevem os pipes se necessário
	if (apply_redirects(cmd->redirs) == -1)
		exit(1);
	shell->cmds = cmd;
	if (is_builtin(shell))
		exit(run_builtin(shell)); // builtin no filho quando há pipe
	external_cmds(shell);
	perror(cmd->args[0]);
	exit(126);
}

void	execute_pipeline(t_shell *shell)
{
	int     pipe_fd[2];
	int     prev_fd = -1;   // read end do pipe anterior
	t_cmd   *cmd = shell->cmds;
	pid_t   last_pid;

	if (ft_setup_heredocs(shell->cmds) == -1)
		return ;
	// Caso especial: comando único builtin sem pipe
	if (!cmd->next && is_builtin(shell))
	{
		run_builtin_in_parent(cmd, shell);
		return ;
	}
	while (cmd)
	{
		// Cria pipe se ainda há comandos a seguir
		if (cmd->next && pipe(pipe_fd) == -1)
		{
			// exit_error("pipe");
			return;
		}
		last_pid = fork();
		if (last_pid == -1)
		{
			// exit_error("fork");
			return;
		}
		if (last_pid == 0)
			child_process(cmd, prev_fd, pipe_fd, shell);

		// Pai fecha os fds que passou ao filho
		if (prev_fd != -1)
			close(prev_fd);
		if (cmd->next)
		{
			close(pipe_fd[1]);       // pai nunca escreve
			prev_fd = pipe_fd[0];    // guarda read end para próximo filho
		}
		cmd = cmd->next;
	}
	// Pai espera por todos os filhos
	waitpid(last_pid, &shell->exit_status, 0);
	while (wait(NULL) > 0)
		;
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
		execute_pipeline(&shell);
			/* return (rl_clear_history(), free_env(shell.env), ft_free_cmd_list(&shell.cmds), shell.exit_status); */
		ft_free_cmd_list(&shell.cmds);
	}
	return (shell.exit_status);
}
