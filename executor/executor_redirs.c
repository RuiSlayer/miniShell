/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_redirs.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slayer <slayer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/31 23:14:58 by fgameiro          #+#    #+#             */
/*   Updated: 2026/04/04 02:50:26 by slayer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/miniShell_exec.h"

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

int	ft_setup_heredocs(t_cmd *cmds)
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
