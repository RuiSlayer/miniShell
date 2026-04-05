/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slayer <slayer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 17:48:49 by Mal               #+#    #+#             */
/*   Updated: 2026/04/05 22:42:40 by slayer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_dprintf(int fd, const char *format, ...)
{
	int				len;
	va_list			params;

	if (!format)
		return (-1);
	va_start(params, format);
	len = 0;
	while (*format)
	{
		if (*format == '%' && *format + 1)
		{
			len += format_delegator(fd, params, format);
			format++;
		}
		else
			len += write(fd, format, 1);
		format++;
	}
	va_end(params);
	return (len);
}

int	ft_printf(const char *format, ...)
{
	int				len;
	va_list			params;

	if (!format)
		return (-1);
	va_start(params, format);
	len = 0;
	while (*format)
	{
		if (*format == '%' && *format + 1)
		{
			len += format_delegator(1, params, format);
			format++;
		}
		else
			len += write(1, format, 1);
		format++;
	}
	va_end(params);
	return (len);
}
