/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slayer <slayer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/17 23:31:38 by slayer            #+#    #+#             */
/*   Updated: 2026/04/17 23:33:43 by slayer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/parser.h"

int	else_branch_parse(t_token **tok, t_cmd	*cmd)
{
	t_redir_type	type;

	type = ft_redir_type(*tok);
	*tok = (*tok)->next;
	if (!*tok || (*tok)->type != T_IDENTIFIER)
	{
		if (!*tok || (*tok)->type == T_EOF)
			ft_syntax_error("newline");
		else
			ft_syntax_error(ft_token_to_str((*tok)->type));
		return (ft_free_cmd_list(&cmd), 1);
	}
	if (!ft_add_redir(cmd, type, (*tok)->value))
		return (ft_free_cmd_list(&cmd), 1);
	return (0);
}
