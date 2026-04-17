/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_lst.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slayer <slayer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 00:35:32 by fgameiro          #+#    #+#             */
/*   Updated: 2026/04/17 23:41:18 by slayer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/parser.h"

static void	ft_copy_args(t_cmd *cmd, char **new_args, bool *new_q, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		new_args[i] = cmd->args[i];
		if (cmd->args_quoted)
			new_q[i] = cmd->args_quoted[i];
		else
			new_q[i] = false;
		i++;
	}
}

int	ft_add_arg(t_cmd *cmd, char *value, bool is_quoted)
{
	int		count;
	char	**new_args;
	bool	*new_q;

	count = 0;
	while (cmd->args && cmd->args[count])
		count++;
	new_args = malloc(sizeof(char *) * (count + 2));
	new_q = malloc(sizeof(bool) * (count + 2));
	if (!new_args || !new_q)
		return (0);
	ft_copy_args(cmd, new_args, new_q, count);
	new_args[count] = ft_strdup(value);
	new_q[count] = is_quoted;
	new_args[count + 1] = NULL;
	new_q[count + 1] = false;
	free(cmd->args);
	free(cmd->args_quoted);
	cmd->args = new_args;
	cmd->args_quoted = new_q;
	return (1);
}

int	ft_add_redir(t_cmd *cmd, t_redir_type type, char *file)
{
	t_redir	*new;
	t_redir	*curr;

	new = ft_calloc(1, sizeof(t_redir));
	if (!new)
		return (0);
	new->type = type;
	new->file = ft_strdup(file);
	if (!cmd->redirs)
		cmd->redirs = new;
	else
	{
		curr = cmd->redirs;
		while (curr->next)
			curr = curr->next;
		curr->next = new;
	}
	return (1);
}
