/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slayer <slayer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 17:14:55 by fgameiro          #+#    #+#             */
/*   Updated: 2026/03/14 17:26:41 by slayer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/tokens.h"

int	ft_is_quote(char c)
{
	if (c == '\'' || c == '"')
		return (1);
	return (0);
}

int	ft_is_separator(char *s)
{
	return (*s == ' ' || *s == '\t' || *s == '<' || *s == '>' || *s == '|');
}

int ft_isspace(int c)
{
    return (c == ' '  || c == '\t' ||
            c == '\n' || c == '\v' ||
            c == '\f' || c == '\r');
}

void	ft_skip_spaces(char **line)
{
	while (**line && ft_isspace(**line))
				(*line)++;
}

bool	ft_skip_quotes(char *line, size_t *i)
{
	char	quote;

	quote = line[*i];
	if (ft_strchr(line + *i + 1, quote))
	{
		(*i)++;
		while (line[*i] != quote)
			(*i)++;
		(*i)++;
		return (true);
	}
	return (false);
}
