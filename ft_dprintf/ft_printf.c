/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgameiro <fgameiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 17:38:36 by rucosta           #+#    #+#             */
/*   Updated: 2026/04/18 21:03:39 by fgameiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putchar(int fd, char c)
{
	write(fd, &c, 1);
	return (1);
}

static int	print_var(int fd, char c, va_list args)
{
	if (c == 'c')
		return (ft_putchar(fd, (char)va_arg(args, int)));
	else if (c == 's')
		return (ft_putstr(fd, va_arg(args, char *)));
	else if (c == 'p')
		return (put_pointer(fd, va_arg(args, void *)));
	else if (c == 'd' || c == 'i')
		return (put_int(fd, va_arg(args, int)));
	else if (c == 'u')
		return (put_unsigned(fd, va_arg(args, unsigned int)));
	else if (c == 'x')
		return (put_hex(fd, va_arg(args, unsigned int), 0));
	else if (c == 'X')
		return (put_hex(fd, va_arg(args, unsigned int), 1));
	else if (c == '%')
		return (ft_putchar(fd, '%'));
	return (0);
}

int	ft_dprintf(int fd, const char *format, ...)
{
	va_list	args;
	int		i;
	int		count;

	if (!format)
		return (-1);
	i = 0;
	count = 0;
	va_start(args, format);
	while (format[i])
	{
		if (format[i] == '%' && format[i + 1])
		{
			count += print_var(fd, format[i + 1], args);
			i += 2;
			continue ;
		}
		count += ft_putchar(fd, format[i]);
		i++;
	}
	va_end(args);
	return (count);
}
