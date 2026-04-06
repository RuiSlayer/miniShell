/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_delegator.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slayer <slayer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/05 22:42:31 by slayer            #+#    #+#             */
/*   Updated: 2026/04/05 22:42:34 by slayer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*get_case(char hcase)
{
	if (hcase == 'x')
		return (HEX_LOWER);
	if (hcase == 'X')
		return (HEX_UPPER);
	return (NULL);
}

int	format_delegator(
	int fd,
	va_list params,
	const char *format
)
{
	format++;
	if (*format == 'c')
		return (print_char(fd, va_arg(params, int)));
	else if (*format == 's')
		return (print_string(fd, va_arg(params, char *)));
	else if (*format == 'p')
		return (print_pointer(fd, va_arg(params, void *)));
	else if (*format == 'd' || *format == 'i')
		return (print_dec_int(fd, va_arg(params, int)));
	else if (*format == 'u')
		return (print_uint(fd, va_arg(params, uint)));
	else if (*format == 'x' || *format == 'X')
		return (print_hex(fd, va_arg(params, uint), get_case(*format)));
	else if (*format == '%')
		return (write(1, format, 1));
	return (0);
}
