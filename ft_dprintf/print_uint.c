/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_uint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slayer <slayer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/05 22:43:51 by slayer            #+#    #+#             */
/*   Updated: 2026/04/05 22:44:03 by slayer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	print_uint(int fd, uint num)
{
	uint	len;
	char	out;

	len = 0;
	if (num >= 10)
		len += print_uint(fd, num / 10);
	out = num % 10 + '0';
	len += write(fd, &out, 1);
	return (len);
}
