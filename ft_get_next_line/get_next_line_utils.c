/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slayer <slayer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 23:04:53 by ruislayer         #+#    #+#             */
/*   Updated: 2025/05/28 23:00:05 by slayer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	get_buff_length(char *buff)
{
	int	i;

	i = 0;
	while (buff[i] != '\n' && buff[i] != '\0')
		++i;
	if (buff[i] == '\n')
		++i;
	return (i);
}

int	get_line_length(char *line)
{
	int	i;

	i = 0;
	while (line && line[i] != '\0')
		++i;
	return (i);
}

void	resize_buff(char *buff)
{
	int		i;
	int		length;

	length = get_buff_length(buff);
	i = 0;
	while (buff[length] != '\0')
	{
		buff[i++] = buff[length++];
	}
	while (i < length)
	{
		buff[i++] = '\0';
	}
}

int	has_newline(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '\n')
			return (1);
		++i;
	}
	return (0);
}

char	*create_line(char *line, char *buff)
{
	int		buff_length;
	int		line_length;
	int		i;
	int		j;
	char	*new_line;

	i = 0;
	j = 0;
	buff_length = get_buff_length(buff);
	line_length = get_line_length(line);
	new_line = malloc(line_length + buff_length + 1);
	if (!new_line)
		return (NULL);
	while (line && line[i] != '\0')
	{
		new_line[i] = line[i];
		++i;
	}
	while (j < buff_length)
	{
		new_line[i++] = buff[j++];
	}
	new_line[i] = '\0';
	free(line);
	return (new_line);
}
