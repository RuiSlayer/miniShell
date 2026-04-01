/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_loop.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rucosta <rucosta@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/01 21:47:26 by rucosta           #+#    #+#             */
/*   Updated: 2026/04/01 22:17:43 by rucosta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/miniShell_exec.h"

static void	child_process(t_cmd *cmd, int prev_fd, int pipe_fd[], t_shell *shell)
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

static void pipe_setup(t_pipe **pipe_s, t_shell *shell)
{
	*pipe_s = malloc(sizeof(t_pipe));
	if (!*pipe_s)
		return ;
	(*pipe_s)->prev_fd = -1;
	(*pipe_s)->cmd = shell->cmds;
}

static void	parent_in_loop(t_pipe *pipe_s)
{
	// Pai fecha os fds que passou ao filho
	if (pipe_s->prev_fd != -1)
		close(pipe_s->prev_fd);
	if (pipe_s->cmd->next)
	{
		close(pipe_s->pipe_fd[1]);       // pai nunca escreve
		pipe_s->prev_fd = pipe_s->pipe_fd[0];    // guarda read end para próximo filho
	}
	pipe_s->cmd = pipe_s->cmd->next;
}

void	execute_pipeline(t_shell *shell)
{
	t_pipe	*pipe_s;

	pipe_setup(&pipe_s, shell);
	if (!pipe_s->cmd->next && is_builtin(shell))
		return (run_builtin_in_parent(pipe_s->cmd, shell));
	while (pipe_s->cmd)
	{
		// Cria pipe se ainda há comandos a seguir
		if (pipe_s->cmd->next && pipe(pipe_s->pipe_fd) == -1)
			return(perror("pipe: failior"));
		pipe_s->last_pid = fork();
		if (pipe_s->last_pid == -1)
			return(perror("fork: failior"));
		if (pipe_s->last_pid == 0)
			child_process(pipe_s->cmd, pipe_s->prev_fd, pipe_s->pipe_fd, shell);
		parent_in_loop(pipe_s);
	}
	// Pai espera por todos os filhos
	waitpid(pipe_s->last_pid, &shell->exit_status, 0);
	while (wait(NULL) > 0)
		;
}
