/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgameiro <fgameiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 17:14:55 by fgameiro          #+#    #+#             */
/*   Updated: 2026/02/11 11:24:45 by fgameiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokens.h"

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

char *ft_strchr(const char *s, int c)
{
    while (*s)
    {
        if (*s == (char)c)
            return ((char *)s);
        s++;
    }
    if ((char)c == '\0')
        return ((char *)s);
    return (NULL);
}

int ft_strncmp(const char *s1, const char *s2, size_t n)
{
    size_t i;

    if (n == 0)
        return (0);
    i = 0;
    while (i < n && s1[i] && s2[i])
    {
        if ((unsigned char)s1[i] != (unsigned char)s2[i])
            return ((unsigned char)s1[i] - (unsigned char)s2[i]);
        i++;
    }
    if (i < n)
        return ((unsigned char)s1[i] - (unsigned char)s2[i]);
    return (0);
}

char *ft_substr(char const *s, unsigned int start, size_t len)
{
    char    *sub;
    size_t  i;
    size_t  s_len;

    if (!s)
        return (NULL);
    s_len = ft_strlen(s);
    if (start >= s_len)
        return (ft_strdup(""));
    if (len > s_len - start)
        len = s_len - start;
    sub = (char *)malloc(len + 1);
    if (!sub)
        return (NULL);
    i = 0;
    while (i < len)
    {
        sub[i] = s[start + i];
        i++;
    }
    sub[i] = '\0';
    return (sub);
}

char *ft_strdup(const char *s)
{
    char    *dup;
    size_t  len;
    size_t  i;

    len = ft_strlen(s);
    dup = (char *)malloc(len + 1);
    if (!dup)
        return (NULL);
    i = 0;
    while (i < len)
    {
        dup[i] = s[i];
        i++;
    }
    dup[i] = '\0';
    return (dup);
}

size_t ft_strlen(const char *s)
{
    size_t i = 0;
    while (s[i])
        i++;
    return (i);
}

void *ft_calloc(size_t count, size_t size)
{
    void    *ptr;
    size_t  total;

    if (size != 0 && count > SIZE_MAX / size)
        return (NULL);  // overflow protection

    total = count * size;
    ptr = malloc(total);
    if (!ptr)
        return (NULL);

    ft_bzero(ptr, total);
    return (ptr);
}

void ft_bzero(void *s, size_t n)
{
    unsigned char *p;

    p = (unsigned char *)s;
    while (n > 0)
    {
        *p = 0;
        p++;
        n--;
    }
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
