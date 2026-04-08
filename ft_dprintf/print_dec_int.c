/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_dec_int.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slayer <slayer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/05 22:43:10 by slayer            #+#    #+#             */
/*   Updated: 2026/04/05 22:43:13 by slayer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	print_dec_int(int fd, int n)
{
	long	decimal;
	int		len;
	char	number;

	len = 0;
	decimal = n;
	if (decimal < 0)
	{
		len += write(fd, "-", 1);
		decimal = -decimal;
	}
	if (decimal >= 10)
		len += print_dec_int(fd, decimal / 10);
	number = (decimal % 10) + '0';
	len += write(fd, &number, 1);
	return (len);
}
