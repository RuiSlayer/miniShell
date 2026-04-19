/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgameiro <fgameiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 18:28:15 by rucosta           #+#    #+#             */
/*   Updated: 2026/04/18 21:03:32 by fgameiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <stddef.h>
# include <fcntl.h>
# include <unistd.h>
# include <string.h>
# include <stdlib.h>
# include <stdio.h>
# include <limits.h>
# include <stdarg.h>
# include <stdint.h>

int			ft_putchar(int fd, char c);
int			ft_putstr(int fd, char *s);
int			put_pointer(int fd, void *ptr);
int			put_hex(int fd, unsigned int n, int uppercase);
int			put_unsigned(int fd, unsigned int n);
int			put_int(int fd, int n);
int			ft_dprintf(int fd, const char *ptr, ...);
#endif