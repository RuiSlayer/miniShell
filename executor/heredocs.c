/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredocs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgameiro <fgameiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 02:02:42 by fgameiro          #+#    #+#             */
/*   Updated: 2026/04/09 20:49:10 by fgameiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/miniShell_exec.h"

int	ft_setup_heredocs(t_cmd *cmds)
{
	t_cmd	*cmd;
	t_redir	*redir;
	int	i;
	

	cmd = cmds;
	i = 0;
	while (cmd)
	{
		redir = cmd->redirs;
		while (redir)
		{
			if (redir->type == R_HEREDOC)
			{
				redir->herefile = ft_strjoin("herefile", ft_itoa(i));
				if (create_heredoc(redir, redir->herefile))
					return (1);
				i++;
			}
			redir = redir->next;
		}
		cmd = cmd->next;
	}
	return (0);
}

int	create_heredoc(t_redir *redir, char *file_name)
{

	redir->heredoc_fd = open(redir->herefile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (redir->heredoc_fd < 0)
		return (perror(errno), 1);
	return (0);
}

int	write_heredoc(t_redir *redir)
{
	char	*line;

	line = NULL;
	while (1)
	{
		line = get_next_line(0);
		if (strcmp(line, redir->file) == 0)
			break ;
		ft_dprintf(redir->heredoc_fd, "%s", line);
		free(line);
	}
	free(line);
}


