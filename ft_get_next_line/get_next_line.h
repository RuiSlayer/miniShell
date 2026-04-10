/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rucosta <rucosta@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 23:05:10 by ruislayer         #+#    #+#             */
/*   Updated: 2025/07/03 18:29:00 by rucosta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 9999
# endif

char	*get_next_line(int fd);
int		get_buff_length(char *buff);
int		get_line_length(char *line);
void	resize_buff(char *buff);
int		has_newline(char *line);
char	*create_line(char *line, char *buff);

#endif