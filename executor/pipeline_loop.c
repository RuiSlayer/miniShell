/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_loop.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rucosta <rucosta@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/01 21:47:26 by rucosta           #+#    #+#             */
/*   Updated: 2026/04/14 23:52:44 by rucosta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/miniShell_exec.h"

static void	child_process(t_pipe *pipe_s, t_shell *shell)
{
	child_signals();
	shell->is_subshell = 1;
	if (pipe_s->prev_fd != -1)
	{
		dup2(pipe_s->prev_fd, STDIN_FILENO);
		close(pipe_s->prev_fd);
	}
	if (pipe_s->cmd->next)
	{
		dup2(pipe_s->pipe_fd[1], STDOUT_FILENO);
		close(pipe_s->pipe_fd[0]);
		close(pipe_s->pipe_fd[1]);
	}
	if (apply_redirects(pipe_s->cmd->redirs) == -1)
	{
		free(pipe_s);
		update_exit_status(shell, 1);
		clean_exit(shell);
	}
	shell->cmds = pipe_s->cmd;
	if (is_builtin(shell))
		return (free(pipe_s), run_builtin(shell), clean_exit(shell));
	free(pipe_s);
	external_cmds(shell);
}

static void	parent_in_loop(t_pipe *pipe_s)
{
	if (pipe_s->prev_fd != -1)
		close(pipe_s->prev_fd);
	if (pipe_s->cmd->next)
	{
		close(pipe_s->pipe_fd[1]);
		pipe_s->prev_fd = pipe_s->pipe_fd[0];
	}
	pipe_s->cmd = pipe_s->cmd->next;
}

int	no_child_cases(t_shell *shell, t_pipe *pipe_s)
{
	if (!(shell->cmds && shell->cmds->args))
		return (redirect_no_coms(shell, pipe_s), 1);
	if (!pipe_s->cmd->next && is_builtin(shell))
		return (run_builtin_in_parent(pipe_s, shell), 1);
	return (0);
}

void	execute_pipeline(t_shell *shell)
{
	t_pipe	*pipe_s;
	int		status;
	int		i;

	i = 0;
	pipe_setup(&pipe_s, shell);
	if (no_child_cases(shell, pipe_s))
		return ;
	while (pipe_s->cmd)
	{
		if (pipe_s->cmd->next && pipe(pipe_s->pipe_fd) == -1)
			return (free(pipe_s), perror("pipe: failior"));
		pipe_s->last_pid = fork();
		i++;
		if (pipe_s->last_pid == -1)
			return (free(pipe_s), perror("fork: failior"));
		if (pipe_s->last_pid == 0)
			child_process(pipe_s, shell);
		parent_in_loop(pipe_s);
	}
	g_signal = CHILD_RUNNING;
	while (i--)
		waitpid(pipe_s->last_pid, &status, 0);
	set_status(shell, status);
	free(pipe_s);
}
