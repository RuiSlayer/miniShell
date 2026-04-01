/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_redirs.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgameiro <fgameiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/31 23:14:58 by fgameiro          #+#    #+#             */
/*   Updated: 2026/04/01 01:06:20 by fgameiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniShell_exec.h"

int	ft_setup_redirs(t_redir *redir)
{
	int	fd;

	while (redir)
	{
		if (redir->type == R_IN)
			fd = open(redir->file, O_RDONLY);
		else if (redir->type == R_OUT)
			fd = open(redir->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else if (redir->type == R_APPEND)
			fd = open(redir->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
		else
		{
			redir = redir->next;
			continue ;
		}
		if (fd == -1)
			return (perror("minishell"), 0);
		if (redir->type == R_IN)
			dup2(fd, STDIN_FILENO);
		else
			dup2(fd, STDOUT_FILENO);
		close(fd);
		redir = redir->next;
	}
	return (1);
}
