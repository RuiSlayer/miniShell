/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slayer <slayer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/05 22:42:50 by slayer            #+#    #+#             */
/*   Updated: 2026/04/05 22:42:55 by slayer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <sys/types.h>
# include <unistd.h>
# define HEX_UPPER "0123456789ABCDEF"
# define HEX_LOWER "0123456789abcdef"
# define NULLSTR "(null)"
# define NULLPTR "(nil)"

typedef unsigned long	t_ulong;
// Write formatted output to stdout.
int				ft_printf(const char *format, ...);
// Write formatted output to a file descriptor `fd`.
int				ft_dprintf(int fd, const char *format, ...);

int				format_delegator(
					int fd,
					va_list params,
					const char *format);
int				print_char(int fd, int c);
int				print_dec_int(int fd, int n);
int				print_pointer(int fd, void *ptr);
int				print_string(int fd, char *str);
int				print_uint(int fd, uint num);
int				print_hex(int fd, uint hex, char *hex_case);

#endif
