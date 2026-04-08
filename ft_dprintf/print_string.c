/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_string.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slayer <slayer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/05 22:43:43 by slayer            #+#    #+#             */
/*   Updated: 2026/04/05 22:43:46 by slayer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	print_string(int fd, char *str)
{
	int	len;

	len = 0;
	if (!str)
		return (write(fd, NULLSTR, 6));
	if (!str)
		str = "(null)";
	while (str[len])
		len += write(fd, (str + len), 1);
	return (len);
}
