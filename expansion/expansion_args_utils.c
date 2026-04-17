/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_args_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slayer <slayer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/17 23:11:16 by slayer            #+#    #+#             */
/*   Updated: 2026/04/17 23:58:45 by slayer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/expansion.h"

size_t	else_branch_count(char *expanded)
{
	size_t	j;
	char	**words;

	if (!expanded || expanded[0] == '\0')
		return (0);
	words = ft_split_words(expanded);
	j = 0;
	while (words && words[j])
		j++;
	ft_free_words(words);
	return (j);
}

size_t	else_branch_args(char *expanded, char **new_args, size_t k)
{
	size_t	j;
	char	**words;

	words = ft_split_words(expanded);
	if (!words)
		return (k);
	if (words)
	{
		j = 0;
		while (words[j])
			new_args[k++] = words[j++];
		free(words);
	}
	return (k);
}
