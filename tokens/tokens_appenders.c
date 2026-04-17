/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_appenders.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slayer <slayer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/01 12:24:29 by fgameiro          #+#    #+#             */
/*   Updated: 2026/04/17 19:48:58 by slayer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/tokens.h"

int	ft_append_separator(t_token_type type, char **line_ptr,
t_token **token_list)
{
	t_token	*token;

	token = ft_new_token(NULL, type);
	if (!token)
		return (0);
	ft_token_list_add_back(token_list, token);
	(*line_ptr)++;
	if (type == T_DLESS || type == T_DGREAT)
		(*line_ptr)++;
	return (1);
}

static bool	ft_has_quotes(char *str, size_t len)
{
	size_t	i;

	i = 0;
	while (i < len)
	{
		if (ft_is_quote(str[i]))
			return (true);
		i++;
	}
	return (false);
}

int	ft_append_identifier(char **line_ptr, t_token **token_list)
{
	char		*tmp_line;
	char		*value;
	t_token		*token;
	size_t		i;

	tmp_line = *line_ptr;
	i = 0;
	while (tmp_line[i] && !ft_is_separator(tmp_line + i))
	{
		if (ft_is_quote(tmp_line[i]))
		{
			if (!ft_skip_quotes(tmp_line, &i))
				return (ft_putstr_fd("minishell: syntax error: unclose_fdd quote\n", 2), 0);
		}
		else
			i++;
	}
	value = ft_substr(tmp_line, 0, i);
	if (!value)
		return (0);
	token = ft_new_token(value, T_IDENTIFIER);
	if (!token)
		return (free(value), 0);
	token->is_quoted = ft_has_quotes(value, i);
	*line_ptr += i;
	return (ft_token_list_add_back(token_list, token), 1);
}
