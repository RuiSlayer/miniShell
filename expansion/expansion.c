/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgameiro <fgameiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 19:52:42 by fgameiro          #+#    #+#             */
/*   Updated: 2026/04/07 20:03:18 by fgameiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/expansion.h"

static int		ft_word_count(char *str)
{
	int	i;
	int	in_word;

	i = 0;
	in_word = 0;
	if (!str)
		return (0);
	while (*str)
	{
		if ((*str != ' ' && *str != '\t' && *str != '\n'))
		{
			if (!in_word)
			{
				in_word = 1;
				i++;
			}
		}
		else
			in_word = 0;
		str++;
	}
	return (i);
}

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

void	ft_expand(t_shell *shell)
{
	t_cmd	*cmd;
	t_redir	*redir;
	int		i;
	char	*original;

	cmd = shell->cmds;
	while (cmd)
	{
		i = 0;
		while (cmd->args && cmd->args[i])
		{
			cmd->args[i] = ft_expand_string(cmd->args[i], shell);
			i++;
		}
		redir = cmd->redirs;
		while (redir)
		{
			if (redir->type != R_HEREDOC)
			{
				original = ft_strdup(redir->file);
				redir->file = ft_expand_string(redir->file, shell);
				if (redir->file == NULL || ft_word_count(redir->file) != 1)
				{
					ft_dprintf(2, "minishell: %s: ambiguous redirect\n", original);
					free(original);
					//update_exit_status for clean exit in main loop;
					return ;
				}
				free(original);
			}
			redir = redir->next;
		}
		cmd = cmd->next;
	}
}
