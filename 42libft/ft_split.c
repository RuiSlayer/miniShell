/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slayer <slayer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 17:26:57 by rucosta           #+#    #+#             */
/*   Updated: 2026/02/26 18:27:50 by slayer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_words(const char *s, char c)
{
	int	count;
	int	in_word;

	count = 0;
	in_word = 0;
	while (*s)
	{
		if (*s != c && !in_word)
		{
			in_word = 1;
			count++;
		}
		else if (*s == c)
			in_word = 0;
		s++;
	}
	return (count);
}

static int	word_len(const char *s, char c)
{
	int	len;

	len = 0;
	while (s[len] && s[len] != c)
		len++;
	return (len);
}

static char	*malloc_word(const char *s, int len)
{
	char	*word;
	int		i;

	i = 0;
	word = malloc(len + 1);
	if (!word)
		return (NULL);
	while (i < len)
	{
		word[i] = s[i];
		i++;
	}
	word[i] = '\0';
	return (word);
}

static int	word_alloc(int i, char const *s, char **ptr, char c)
{
	int	wlen;

	wlen = word_len(s, c);
	ptr[i] = malloc_word(s, wlen);
	if (!ptr)
	{
		while (i--)
			free(ptr[i]);
		free(ptr[i]);
		free(ptr);
		return (-1);
	}
	return (wlen);
}

char	**ft_split(char const *s, char c)
{
	char	**ptr;
	int		i;
	int		wlen;

	if (!s)
		return (NULL);
	ptr = malloc(sizeof(char *) * (count_words(s, c) + 1));
	if (!ptr)
		return (NULL);
	i = 0;
	while (*s)
	{
		if (*s != c)
		{
			wlen = word_alloc(i, s, ptr, c);
			if (wlen == -1)
				return (NULL);
			s += wlen;
			i++;
		}
		else
			s++;
	}
	ptr[i] = NULL;
	return (ptr);
}
