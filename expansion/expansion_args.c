/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_args.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgameiro <fgameiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/15 21:59:26 by fgameiro          #+#    #+#             */
/*   Updated: 2026/04/16 03:31:12 by fgameiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/expansion.h"

static char	**ft_expand_all(char **old_args, size_t len, t_shell *shell)
{
	char	**expanded;
	size_t	i;

	expanded = malloc(sizeof(char *) * (len + 1));
	if (!expanded)
		return (NULL);
	i = 0;
	while (i < len)
	{
		expanded[i] = ft_expand_string(ft_strdup(old_args[i]), shell);
		if (!expanded[i])
			return (ft_free_expanded(expanded, i), NULL);
		i++;
	}
	expanded[len] = NULL;
	return (expanded);
}

static size_t	ft_count_words_total(char **expanded,
				size_t len, bool *quoted)
{
	size_t	total;
	size_t	i;
	char	**words;
	size_t	j;

	total = 0;
	i = 0;
	while (i < len)
	{
		if (expanded[i] && expanded[i][0] == '\0'
			&& (!quoted || !quoted[i]))
		{
			i++;
			continue ;
		}
		if (quoted && quoted[i])
			total++;
		else
		{
			words = ft_split_words(expanded[i]);
			j = 0;
			while (words && words[j])
				j++;
			total += j;
			ft_free_words(words);
		}
		i++;
	}
	return (total);
}

static void	ft_fill_new_args(char **expanded, size_t len,
			char **new_args, bool *quoted)
{
	size_t	i;
	size_t	j;
	size_t	k;
	char	**words;

	k = 0;
	i = 0;
	while (i < len)
	{
		if (!expanded[i] && expanded[i][0] == '\0'
			&& (!quoted || !quoted[i]))
		{
				i++;
				continue;
		}
		if (quoted && quoted[i])
			new_args[k++] = ft_strdup(expanded[i]);
		else
		{
			words = ft_split_words(expanded[i]);
			if (words)
			{
				j = 0;
				while (words[j])
					new_args[k++] = words[j++];
				free(words);
			}
		}
		i++;
	}
	new_args[k] = NULL;
}

void ft_free_old_args(char **args)
{
	size_t i;

	if (!args)
		return ;
	i = 0;
	while (args[i])
		free(args[i++]);
	free(args);
}

char	**ft_expand_args(char **old_args, bool *quoted, t_shell *shell)
{
	char	**expanded;
	char	**new_args;
	size_t	old_len;
	size_t	new_len;

	old_len = 0;
	while (old_args[old_len])
		old_len++;
	expanded = ft_expand_all(old_args, old_len, shell);
	if (!expanded)
		return (NULL);
	new_len = ft_count_words_total(expanded, old_len, quoted);
	new_args = malloc(sizeof(char *) * (new_len + 1));
	if (!new_args)
		return (ft_free_expanded(expanded, old_len), NULL);
	ft_fill_new_args(expanded, old_len, new_args, quoted);
	ft_free_expanded(expanded, old_len);
	return (new_args);
}
