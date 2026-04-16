/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_quotes.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgameiro <fgameiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/23 15:05:03 by fgameiro          #+#    #+#             */
/*   Updated: 2026/04/16 03:31:17 by fgameiro         ###   ########.fr       */
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

void	ft_handle_double_quote(char *str, size_t *i,
	char **result, t_shell *shell)
{
	(*i)++;
	while (str[*i] && str[*i] != '"')
	{
		if (str[*i] == '$')
			ft_handle_expansion(str, i, result, shell);
		else
		{
			ft_append_char(result, str[*i]);
			(*i)++;
		}
	}
	(*i)++;
}

char	*ft_expand_string(char *str, t_shell *shell)
{
	char	*result;
	size_t	i;

	result = ft_strdup("");
	i = 0;
	while (str[i])
	{
		if (str[i] == '\'')
			ft_handle_single_quote(str, &i, &result);
		else if (str[i] == '"')
			ft_handle_double_quote(str, &i, &result, shell);
		else if (str[i] == '$' && str[i])
			ft_handle_expansion(str, &i, &result, shell);
		else
			ft_append_char(&result, str[i++]);
	}
	free(str);
	return (result);
}

void	ft_free_words(char **words)
{
	size_t	j;

	if (!words)
		return ;
	j = 0;
	while (words[j])
		free(words[j++]);
	free(words);
}

void	ft_free_expanded(char **expanded, size_t len)
{
	size_t	i;

	i = 0;
	while (i < len)
		free(expanded[i++]);
	free(expanded);
}
