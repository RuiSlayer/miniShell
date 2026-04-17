/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_loop_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slayer <slayer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/17 19:46:57 by slayer            #+#    #+#             */
/*   Updated: 2026/04/17 20:51:22 by slayer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/miniShell_exec.h"

void	close_fd(int *fd)
{
	if (*fd != -1)
	{
		close(*fd);
		*fd = -1;
	}
}

void	close_fd_heredocs(t_cmd *cmd)
{
	t_redir	*r;

	r = cmd->redirs;
	while (r)
	{
		if (r->type == R_HEREDOC && r->heredoc_fd != -1)
		{
			close_fd(&r->heredoc_fd);
			r->heredoc_fd = -1;
		}
		r = r->next;
	}
}

void	close_fd_all_heredocs(t_cmd *cmds)
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
					close_fd(&r->heredoc_fd);
					r->heredoc_fd = -1;
				}
			}
			r = r->next;
		}
		c = c->next;
	}
}
