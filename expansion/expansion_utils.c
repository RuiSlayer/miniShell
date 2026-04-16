/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgameiro <fgameiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 19:52:39 by fgameiro          #+#    #+#             */
/*   Updated: 2026/04/16 01:25:38 by fgameiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/expansion.h"

void	ft_append_char(char **result, char c)
{
	char	*tmp;
	char	buf[2];

	buf[0] = c;
	buf[1] = '\0';
	tmp = ft_strjoin(*result, buf);
	free(*result);
	*result = tmp;
}

void	ft_append_str(char **result, char *str)
{
	char	*tmp;

	if (!str)
		return ;
	tmp = ft_strjoin(*result, str);
	free(*result);
	*result = tmp;
}

void	normalize_cmd(t_cmd *cmd)
{
	if (!cmd)
		return;
	if (!cmd->args)
	{
		cmd->is_empty = 1;
		return ;
	}
	if (!cmd->args || !cmd->args[0])
	{
		ft_free_old_args(cmd->args);
		cmd->args = NULL;
		cmd->is_empty = 1;
		return;
	}
	cmd->is_empty = 0;
}

void normalize_all_cmds(t_shell *shell)
{
	t_cmd *tmp = shell->cmds;

	while (tmp)
	{
		normalize_cmd(tmp);
		tmp = tmp->next;
	}
}
