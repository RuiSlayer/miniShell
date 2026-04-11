/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgameiro <fgameiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 23:04:35 by ruislayer         #+#    #+#             */
/*   Updated: 2026/04/09 03:49:19 by fgameiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char	buff[BUFFER_SIZE + 1];
	char		*line;
	int			bytes_read;

	bytes_read = BUFFER_SIZE;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	line = NULL;
	while (1)
	{
		if (buff[0] == '\0')
			bytes_read = read(fd, buff, BUFFER_SIZE);
		if (bytes_read == 0)
			return (line);
		if (bytes_read < 0)
			return (free(line), NULL);
		line = create_line(line, buff);
		if (!line)
			return (NULL);
		resize_buff(buff);
		if (has_newline(line))
			return (line);
	}
	return (line);
}
