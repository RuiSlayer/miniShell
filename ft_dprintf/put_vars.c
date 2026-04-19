/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_vars.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgameiro <fgameiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 22:15:35 by rucosta           #+#    #+#             */
/*   Updated: 2026/04/18 21:02:30 by fgameiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putstr(int fd, char *s)
{
	int	i;

	if (!s)
		return (ft_putstr(fd, "(null)"));
	i = 0;
	while (s[i] != '\0')
	{
		ft_putchar(fd, s[i]);
		i++;
	}
	return (i);
}

int	put_pointer(int fd, void *ptr)
{
	uintptr_t	address;
	char		buf[16];
	int			i;
	int			size;
	char		*base;

	address = (uintptr_t)ptr;
	if (address == 0)
		return (ft_putstr(fd, "(nil)"));
	i = 0;
	base = "0123456789abcdef";
	while (address)
	{
		buf[i++] = base[address % 16];
		address /= 16;
	}
	size = i;
	ft_putstr(fd, "0x");
	while (i--)
		ft_putchar(fd, buf[i]);
	return (size + 2);
}

int	put_hex(int fd, unsigned int n, int uppercase)
{
	char	*base;
	char	buf[8];
	int		i;
	int		size;

	i = 0;
	if (uppercase)
		base = "0123456789ABCDEF";
	else
		base = "0123456789abcdef";
	if (n == 0)
		return (ft_putchar(fd, '0'));
	while (n)
	{
		buf[i++] = base[n % 16];
		n /= 16;
	}
	size = i;
	while (i--)
		ft_putchar(fd, buf[i]);
	return (size);
}

int	put_unsigned(int fd, unsigned int n)
{
	char	buf[10];
	int		i;
	int		size;

	i = 0;
	if (n == 0)
		return (ft_putchar(fd, '0'));
	while (n)
	{
		buf[i++] = (n % 10) + '0';
		n /= 10;
	}
	size = i;
	while (i--)
		ft_putchar(fd, buf[i]);
	return (size);
}

int	put_int(int fd, int n)
{
	if (n < 0)
		return (ft_putchar(fd, '-') + put_unsigned(fd, -n));
	return (put_unsigned(fd, n));
}
