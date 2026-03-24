/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgameiro <fgameiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 19:52:42 by fgameiro          #+#    #+#             */
/*   Updated: 2026/03/24 16:40:08 by fgameiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/expansion.h"

void	ft_handle_expansion(char *str, size_t *i, char **result, char **env, int exit_status)
{
	char	*var_name;
	char	*value;

	var_name = ft_get_var_name(str, i);
	if (!var_name)
		return ;
	if (ft_strcmp(var_name, "?") == 0)
		value = ft_itoa(exit_status);
	else
		value = ft_getenv(env, var_name);
	if (value)
		ft_append_str(result, value);
	free(var_name);
}

void	ft_expand(t_cmd *cmds, char **env, int exit_status)
{
	t_cmd	*cmd;
	t_redir	*redir;
	int		i;

	cmd = cmds;
	while (cmd)
	{
		i = 0;
		while (cmd->args && cmd->args[i])
		{
			cmd->args[i] = ft_expand_string(cmd->args[i], exit_status);
			i++;
		}
		redir = cmd->redirs;
		while (redir)
		{
			if (redit->type != R_HEREDOC)
				redir->type = ft_expand_string(redir->file, exit_status);
		}
		cmd = cmd->next;
	}
}
