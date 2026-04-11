/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slayer <slayer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/10 11:51:21 by fgameiro          #+#    #+#             */
/*   Updated: 2026/04/11 18:38:14 by slayer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/parser.h"

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

static char	*ft_token_to_str(t_token_type type)
{
	if (type == T_LESS)
		return ("<");
	if (type == T_GREAT)
		return (">");
	if (type == T_DLESS)
		return ("<<");
	if (type == T_DGREAT)
		return (">>");
	if (type == T_PIPE)
		return ("|");
	return (NULL);
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
		if ((*tok)->type == T_IDENTIFIER)
		{
			if (!ft_add_arg(cmd, (*tok)->value))
				return (ft_free_cmd_list(&cmd), NULL);
			*tok = (*tok)->next;
		}
		else
		{
			type = ft_redir_type(*tok);
			*tok = (*tok)->next;
			if (!*tok || (*tok)->type != T_IDENTIFIER)
			{
				if (!*tok || (*tok)->type == T_EOF)
					ft_syntax_error("newline");
				else
					ft_syntax_error(ft_token_to_str((*tok)->type));
				return (ft_free_cmd_list(&cmd), NULL);
			}
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

	if ((*tok)->type == T_PIPE)
		return (NULL);
	head = ft_parse_command(tok);
	if (!head)
		return (NULL);
	curr = head;
	while ((*tok)->type == T_PIPE)
	{
		*tok = (*tok)->next;
		if ((*tok)->type == T_EOF || (*tok)->type == T_PIPE)
		{
			ft_syntax_error("|");
			return (ft_free_cmd_list(&head), NULL);
		}
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

	if (!tokens)
		return (NULL);
	if (tokens->type == T_PIPE)
		return (ft_syntax_error(ft_token_to_str((tokens)->type)), NULL);
	cmds = ft_parse_pipeline(&tokens);
	return (cmds);
}
