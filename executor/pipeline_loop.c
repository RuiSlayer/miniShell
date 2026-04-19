/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_loop.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgameiro <fgameiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/01 21:47:26 by rucosta           #+#    #+#             */
/*   Updated: 2026/04/18 20:46:26 by fgameiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/miniShell_exec.h"

static void	child_process(t_pipe *pipe_s, t_shell *shell)
{
	child_signals();
	shell->is_inchild = 1;
	if (pipe_s->prev_fd != -1)
	{
		dup2(pipe_s->prev_fd, STDIN_FILENO);
		close_fd(&pipe_s->prev_fd);
	}
	if (pipe_s->cmd->next)
	{
		dup2(pipe_s->pipe_fd[1], STDOUT_FILENO);
		close_fd(&pipe_s->pipe_fd[0]);
		close_fd(&pipe_s->pipe_fd[1]);
	}
	if (apply_redirects(pipe_s->cmd->redirs) == -1)
	{
		free_pipe(pipe_s);
		update_exit_status(shell, 1);
		clean_exit(shell);
	}
	close_fd_heredocs(pipe_s->cmd);
	shell->cmds = pipe_s->cmd;
	if (is_builtin(shell))
		return (free_pipe(pipe_s), run_builtin(shell), clean_exit(shell));
	free_pipe(pipe_s);
	external_cmds(shell);
}

static void	parent_in_loop(t_pipe *pipe_s)
{
	if (pipe_s->prev_fd != -1)
		close_fd(&pipe_s->prev_fd);
	if (pipe_s->cmd->next)
	{
		close_fd(&pipe_s->pipe_fd[1]);
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

void	pipeline_loop(t_shell *shell, t_pipe *pipe_s, int i)
{
	if (pipe_s->cmd->next && pipe(pipe_s->pipe_fd) == -1)
		return (free_pipe(pipe_s), perror("pipe: failior"));
	pipe_s->pids[i] = fork();
	if (pipe_s->pids[i] == -1)
		return (free_pipe(pipe_s), perror("fork: failior"));
	if (pipe_s->pids[i] == 0)
		child_process(pipe_s, shell);
	close_fd_heredocs(pipe_s->cmd);
	parent_in_loop(pipe_s);
}

void	execute_pipeline(t_shell *shell)
{
	t_pipe	*pipe_s;
	int		status;
	int		last_status;
	int		i;

	i = 0;
	last_status = 0;
	pipe_setup(&pipe_s, shell);
	if (no_child_cases(shell, pipe_s))
		return ;
	g_signal = CHILD_RUNNING;
	while (pipe_s->cmd)
	{
		pipeline_loop(shell, pipe_s, i);
		i++;
	}
	while (i-- > 0)
	{
		waitpid(pipe_s->pids[i], &status, 0);
		if (i == shell->cmd_count - 1)
			last_status = status;
	}
	set_status(shell, last_status);
	free_pipe(pipe_s);
}
