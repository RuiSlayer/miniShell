/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_quotes.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgameiro <fgameiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/23 15:05:03 by fgameiro          #+#    #+#             */
/*   Updated: 2026/03/23 16:05:08 by fgameiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/expansion.h"

void	ft_handle_single_quote(char *str, size_t *i, char **result)
{
	(*i)++;
	while (str[*i] && str[*i] != '\'')
	{
		ft_append_char(result, str[*i]);
		(*i)++;
	}
	(*i)++;
}

void	ft_handle_double_quote(char *str, size_t *i, char **result, int exit_status)
{
	(*i)++;
	while (str[*i] && str[*i] != '"')
	{
		if (str[*i] == '$')
			ft_handle_expansion(str, i, result, exit_status);
		else
		{
			ft_append_char(result, str[*i]);
			(*i)++;
		}
	}
	(i*)++;
}

char	*ft_expand_string(char *str, int exit_status)
{
	char	*result;
	size_t	i;

	result = ft_strdup("")
}
