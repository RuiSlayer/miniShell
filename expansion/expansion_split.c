/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_split.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgameiro <fgameiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/15 21:59:47 by fgameiro          #+#    #+#             */
/*   Updated: 2026/04/15 21:59:50 by fgameiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/expansion.h"

static size_t	ft_count_words(char *str)
{
	size_t	count;
	size_t	i;

	count = 0;
	i = 0;
	while (str[i])
	{
		while (str[i] && ft_isspace(str[i]))
			i++;
		if (str[i])
		{
			count++;
			while (str[i] && !ft_isspace(str[i]))
				i++;
		}
	}
	return (count);
}

static void	ft_fill_words(char *str, char **words)
{
	size_t	i;
	size_t	start;
	size_t	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		while (str[i] && ft_isspace(str[i]))
			i++;
		if (!str[i])
			break ;
		start = i;
		while (str[i] && !ft_isspace(str[i]))
			i++;
		words[count++] = ft_substr(str, start, i - start);
	}
	words[count] = NULL;
}

char	**ft_split_words(char *str)
{
	char	**words;
	size_t	count;

	count = ft_count_words(str);
	words = malloc(sizeof(char *) * (count + 1));
	if (!words)
		return (NULL);
	ft_fill_words(str, words);
	return (words);
}