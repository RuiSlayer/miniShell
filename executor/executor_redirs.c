/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_redirs.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slayer <slayer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/31 23:14:58 by fgameiro          #+#    #+#             */
/*   Updated: 2026/04/17 20:59:47 by slayer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/miniShell_exec.h"

int	clear_after(char *line, int pipefd[], char *delimiter, t_redir *redir)
{
	free(line);
	free(delimiter);
	setup_signals();
	close_fd(&pipefd[1]);
	rl_event_hook = NULL;
	if (g_signal == SIGINT)
	{
		close_fd(&pipefd[0]);
		redir->heredoc_fd = -1;
		return (1);
	}
	redir->heredoc_fd = pipefd[0];
	return (0);
}

int	heredoc_loop_breaks(char *line, char *delimiter)
{
	if (!line)
	{
		ft_putstr_fd("minishell: warning: here-document delimited by end-of-file (wanted `", STDERR_FILENO);
		ft_putstr_fd(delimiter, STDERR_FILENO);
		ft_putstr_fd("')\n", STDERR_FILENO);
		return (1);
	}
	if (g_signal == SIGINT)
		return (1);
	if (!line || ft_strcmp(line, delimiter) == 0)
		return (1);
	return (0);
}

int	apply_heredoc(t_redir *redir, t_shell *shell)
{
	int		pipefd[2];
	char	*line;
	char	*delimiter;
	char	*expanded;

	g_signal = HEREDOC_RUNNING;
	if (pipe(pipefd) == -1)
		return (perror("pipe"), -1);
	delimiter = ft_strip_delimiter(redir->file);
	if (!delimiter)
		return (close_fd(&pipefd[0]), close_fd(&pipefd[1]), -1);
	g_signal = HEREDOC_RUNNING;
	heredoc_signals();
	rl_event_hook = heredoc_event_hook;
	while (1)
	{
		line = readline("> ");
		if (heredoc_loop_breaks(line, delimiter))
			break ;
		if (!(ft_strchr(redir->file, '\'') || ft_strchr(redir->file, '"')))
		{
			expanded = expand_heredoc(line, shell);
			free(line);
			line = expanded;
		}
		write(pipefd[1], line, ft_strlen(line));
		write(pipefd[1], "\n", 1);
		free(line);
	}
	return (clear_after(line, pipefd, delimiter, redir));
}

int	ft_setup_heredocs(t_cmd *cmds, t_shell *shell)
{
	t_cmd	*cmd;
	t_redir	*redir;

	cmd = cmds;
	while (cmd)
	{
		redir = cmd->redirs;
		while (redir)
		{
			if (redir->type == R_HEREDOC)
			{
				if (apply_heredoc(redir, shell) != 0)
					return (-1);
			}
			redir = redir->next;
		}
		cmd = cmd->next;
	}
	return (0);
}

int	apply_redirects(t_redir *redir)
{
	int	fd;

	while (redir)
	{
		if (redir->type == R_HEREDOC)
		{
			dup2(redir->heredoc_fd, STDIN_FILENO);
			close_fd(&redir->heredoc_fd);
		}
		else
		{
			fd = open_fd(redir);
			if (fd == -1)
				return (perror(redir->file), -1);
			if (redir->type == R_IN)
				dup2(fd, STDIN_FILENO);
			else
				dup2(fd, STDOUT_FILENO);
			close_fd(&fd);
		}
		redir = redir->next;
	}
	return (0);
}
