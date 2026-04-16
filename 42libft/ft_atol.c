/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rucosta <rucosta@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/15 04:30:10 by rucosta           #+#    #+#             */
/*   Updated: 2026/04/15 04:30:22 by rucosta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

long	ft_atol(const char *s)
{
	size_t	i;
	long	sign;
	long	num;

	i = 0;
	num = 0;
	sign = 1;
	while (ft_isspace(s[i]))
		i++;
	if (s[i] == '+' || s[i] == '-')
	{
		if (s[i] == '-')
			sign *= -1;
		i++;
	}
	while (ft_isdigit(s[i]))
	{
		num = num * 10 + (s[i] - '0');
		if (num * sign < INT_MIN || num * sign > INT_MAX)
			return (LONG_MAX);
		i++;
	}
	return (num * sign);
}
