/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_hex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slayer <slayer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/05 22:43:24 by slayer            #+#    #+#             */
/*   Updated: 2026/04/05 22:43:27 by slayer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	print_hex(int fd, uint hex, char *hex_case)
{
	int		len;
	char	out;

	len = 0;
	if (hex >= 16)
		len += print_hex(fd, hex / 16, hex_case);
	out = hex_case[hex % 16];
	len += write(fd, &out, 1);
	return (len);
}
