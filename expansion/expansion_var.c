/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_var.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgameiro <fgameiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/23 15:05:35 by fgameiro          #+#    #+#             */
/*   Updated: 2026/04/06 23:20:46 by fgameiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/expansion.h"

char	*ft_get_var_name(char *str, size_t *i)
{
	size_t	start;

	(*i)++;
	if (str[*i] == '{')
	{
		(*i)++;
		start = *i;
		while (str[*i] && str[*i] != '}')
			(*i)++;
		if (str[*i] == '}')
			(*i)++;
		return (ft_substr(str, start, *i - start - 1));
	}
	if (!str[*i] || ft_isspace(str[*i]))
		return (ft_strdup(""));
	if (str[*i] == '?')
	{
		(*i)++;
		return (ft_strdup("?"));
	}
	start = *i;
	while (str[*i] && (ft_isalnum(str[*i]) || str[*i] == '_'))
		(*i)++;
	return (ft_substr(str, start, *i - start));
}
