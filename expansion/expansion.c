/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slayer <slayer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 19:52:42 by fgameiro          #+#    #+#             */
/*   Updated: 2026/04/16 19:18:49 by slayer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/expansion.h"

void	ft_handle_expansion(char *str, size_t *i, char **result, t_shell *shell)
{
	char	*var_name;
	char	*value;

	var_name = ft_get_var_name(str, i);
	if (!var_name)
		return ;
	if (ft_strlen(var_name) == 0)
	{
		free(var_name);
		ft_append_char(result, '$');
		return ;
	}
	if (ft_strcmp(var_name, "?") == 0)
	{
		value = ft_itoa(shell->exit_status);
		ft_append_str(result, value);
		free(value);
	}
	else
	{
		value = ft_getenv(shell->env, var_name);
		if (value)
			ft_append_str(result, value);
	}
	free(var_name);
}

int	ft_expand(t_shell *shell)
{
	t_cmd	*cmd;
	t_redir	*redir;
	char	**new_args;
	char	*original;

	cmd = shell->cmds;
	while (cmd)
	{
		if (cmd->args)
		{
			new_args = ft_expand_args(cmd->args, cmd->args_quoted, shell);
			ft_free_old_args(cmd->args);
			free(cmd->args_quoted);
			cmd->args = new_args;
			cmd->args_quoted = NULL;
		}
		redir = cmd->redirs;
		while (redir)
		{
			if (redir->type != R_HEREDOC)
			{
				original = ft_strdup(redir->file);
				redir->file = ft_expand_string(redir->file, shell);
				if (redir->file == NULL)
				{
					ft_dprintf(2, "minishell: %s: ambiguous redirect\n", original);
					free(original);
					redir->file = NULL;
					return (-1);
				}
				free(original);
			}
			redir = redir->next;
		}
		cmd = cmd->next;
	}
	return (0);
}
