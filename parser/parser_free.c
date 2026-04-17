/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_free.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slayer <slayer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 00:09:09 by fgameiro          #+#    #+#             */
/*   Updated: 2026/04/17 19:48:58 by slayer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/parser.h"

/* void	clear_heredocs(t_cmd	*curr)
{

	if(curr->redirs->heredoc_fd)
	{
		close_fd(curr->redirs->heredoc_fd);
		unlink(curr->redirs->herefile);
	}

} */

void	ft_free_redir_list(t_redir *redir)
{
	t_redir	*next;

	while (redir)
	{
		next = redir->next;
		free(redir->herefile);
		free(redir->file);
		free(redir);
		redir = next;
	}
}

void	ft_free_cmd_list(t_cmd **lst)
{
	t_cmd	*next;
	t_cmd	*curr;
	int		i;

	curr = *lst;
	while (curr)
	{
		next = curr->next;
		if (curr->args)
		{
			i = 0;
			while (curr->args[i])
				free(curr->args[i++]);
			free(curr->args);
			if (curr->args_quoted)
				free(curr->args_quoted);
		}
		ft_free_redir_list(curr->redirs);
		free(curr);
		curr = next;
	}
	*lst = NULL;
}
