/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgameiro <fgameiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/10 11:51:21 by fgameiro          #+#    #+#             */
/*   Updated: 2026/03/12 16:14:55 by fgameiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static t_redir_type	ft_redir_type(t_token *tok)
{
	if (tok->type == T_LESS)
		return (R_IN);
	if (tok->type == T_GREAT)
		return (R_OUT);
	if (tok->type == T_DLESS)
		return (R_HEREDOC);
	return (R_APPEND);
}

t_cmd	*ft_parse_command(t_token **tok)
{
	t_cmd			*cmd;
	t_redir_type	type;

	cmd = ft_calloc(1, sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	while ((*tok)->type != T_PIPE && (*tok)->type != T_EOF)
	{
		if ((*tok)->type == T_IDENTIFIER){
			if (!ft_add_arg(cmd, (*tok)->value))
				return (ft_free_cmd_list(&cmd), NULL);
			*tok = (*tok)->next;
		}
		else
		{
			type = ft_redir_type(*tok);
			*tok = (*tok)->next;
			if ((*tok)->type != T_IDENTIFIER)
				return (ft_free_cmd_list(&cmd), NULL);
			if (!ft_add_redir(cmd, type, (*tok)->value))
				return (ft_free_cmd_list(&cmd), NULL);
			*tok = (*tok)->next;
		}
	}
	return (cmd);
}

t_cmd	*ft_parse_pipeline(t_token **tok)
{
	t_cmd	*head;
	t_cmd	*curr;
	t_cmd	*new;

	if((*tok)->type == T_PIPE)
		return (NULL);
	head = ft_parse_command(tok);
	if (!head)
		return (NULL);
	curr = head;
	while ((*tok)->type == T_PIPE)
	{
		*tok = (*tok)->next;
		if ((*tok)->type == T_EOF || (*tok)->type == T_PIPE)
			return (ft_free_cmd_list(&head), NULL);
		new = ft_parse_command(tok);
		if (!new)
			return (ft_free_cmd_list(&head), NULL);
		curr->next = new;
		curr = new;
	}
	return (head);
}

t_cmd	*ft_parse(t_token *tokens)
{
	t_cmd	*cmds;
	
	if (!tokens || tokens->type == T_EOF)
		return (NULL);
	cmds = ft_parse_pipeline(&tokens);
	return (cmds);
}
//From this line down, functions meant for testing
/* void	print_cmd_list(t_cmd *cmds)
{
	t_cmd   *cmd;
    t_redir *redir;
    int     i;
    int     cmd_num;

    cmd = cmds;
    cmd_num = 1;
    while (cmd)
    {
        printf("--- CMD %d ---\n", cmd_num++);
        i = 0;
        while (cmd->args && cmd->args[i])
            printf("  arg[%d]: %s\n", i, cmd->args[i++]);
        redir = cmd->redirs;
        while (redir)
        {
            printf("  redir: %d -> %s\n", redir->type, redir->file);
            redir = redir->next;
        }
        cmd = cmd->next;
    }
} */


