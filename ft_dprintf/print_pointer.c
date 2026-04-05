/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_pointer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slayer <slayer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/05 22:43:34 by slayer            #+#    #+#             */
/*   Updated: 2026/04/05 22:43:37 by slayer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	print_hex_ptr(int fd, unsigned long hex)
{
	int		len;
	char	out;

	len = 0;
	if (hex >= 16)
		len += print_hex_ptr(fd, hex / 16);
	out = HEX_LOWER[hex % 16];
	len += write(fd, &out, 1);
	return (len);
}

int	print_pointer(int fd, void *ptr)
{
	int			len;
	t_ulong		pointer;

	len = 0;
	pointer = (t_ulong) ptr;
	if (!pointer)
		return (write(fd, NULLPTR, 5));
	len += write(fd, "0x", 2);
	len += print_hex_ptr(fd, pointer);
	return (len);
}
