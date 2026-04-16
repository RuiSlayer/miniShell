/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_loop_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgameiro <fgameiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/11 18:44:24 by slayer            #+#    #+#             */
/*   Updated: 2026/04/16 00:24:47 by fgameiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/miniShell_exec.h"

void	pipe_setup(t_pipe **pipe_s, t_shell *shell)
{
	*pipe_s = malloc(sizeof(t_pipe));
	if (!*pipe_s)
		return ;
	(*pipe_s)->pipe_fd[0] = -1;
	(*pipe_s)->pipe_fd[1] = -1;
	(*pipe_s)->prev_fd = -1;
	(*pipe_s)->pipe_count = 0;
	(*pipe_s)->cmd = shell->cmds;
}

void	set_status(t_shell *shell, int status)
{
	if (WIFSIGNALED(status) && WTERMSIG(status) == SIGQUIT)
		ft_dprintf(2, "Quit (core dumped)\n");
	if (WIFEXITED(status))
		shell->exit_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		shell->exit_status = 128 + WTERMSIG(status);
	g_signal = 0;
	shell->is_subshell = 0;
	setup_signals();
}

void	redirect_no_coms(t_shell *shell, t_pipe *pipe_s)
{
	int	saved_stdin;
	int	saved_stdout;

	saved_stdin = dup(STDIN_FILENO);
	saved_stdout = dup(STDOUT_FILENO);
	if (apply_redirects(pipe_s->cmd->redirs) == -1)
	{
		update_exit_status(shell, 1);
		close(saved_stdin);
		close(saved_stdout);
		free(pipe_s);
		return ;
	}
	dup2(saved_stdin, STDIN_FILENO);
	dup2(saved_stdout, STDOUT_FILENO);
	close(saved_stdin);
	close(saved_stdout);
	free(pipe_s);
	return ;
}

void	close_heredocs(t_cmd *cmd)
{
	t_redir	*r;
	
	r = cmd->redirs;

	while (r)
	{
		if (r->type == R_HEREDOC && r->heredoc_fd != -1)
		{
			close(r->heredoc_fd);
			r->heredoc_fd = -1;
		}
		r = r->next;
	}
}

void	close_all_heredocs(t_cmd *cmds)
{
	t_cmd	*c;
	t_redir	*r;

	c = cmds;
	while (c)
	{
		r = c->redirs;
		while (r)
		{
			if (r->type == R_HEREDOC)
			{
				if (r->heredoc_fd != -1)
				{
					close(r->heredoc_fd);
					r->heredoc_fd = -1;
				}
			}
			r = r->next;
		}
		c = c->next;
	}
}
