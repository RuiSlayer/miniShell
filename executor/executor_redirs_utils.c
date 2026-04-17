/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_redirs_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slayer <slayer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/17 20:56:16 by slayer            #+#    #+#             */
/*   Updated: 2026/04/17 21:00:02 by slayer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/miniShell_exec.h"

void	ft_strip_quoted(char *str, int *i, char **result)
{
	char	quote;

	quote = str[(*i)++];
	while (str[*i] && str[*i] != quote)
	{
		ft_append_char(result, str[*i]);
		(*i)++;
	}
	if (str[*i])
		(*i)++;
}

char	*ft_strip_delimiter(char *str)
{
	char	*result;
	int		i;

	result = ft_strdup("");
	i = 0;
	while (str[i])
	{
		if (str[i] == '"' || str[i] == '\'')
			ft_strip_quoted(str, &i, &result);
		else
		{
			ft_append_char(&result, str[i]);
			i++;
		}
	}
	return (result);
}

char	*expand_heredoc(char *line, t_shell *shell)
{
	size_t	i;
	char	*res;

	res = ft_strdup("");
	if (!res)
		return (NULL);
	i = 0;
	while (line[i])
	{
		if (line[i] == '\'')
			ft_handle_single_quote(line, &i, &res);
		else if (line[i] == '$')
			ft_handle_expansion(line, &i, &res, shell);
		else
		{
			ft_append_char(&res, line[i]);
			i++;
		}
	}
	return (res);
}

int	open_fd(t_redir	*redir)
{
	if (redir->type == R_IN)
		return (open(redir->file, O_RDONLY));
	if (redir->type == R_OUT)
		return (open(redir->file, O_WRONLY | O_CREAT | O_TRUNC, 0644));
	if (redir->type == R_APPEND)
		return (open(redir->file, O_WRONLY | O_CREAT | O_APPEND, 0644));
	return (-1);
}
