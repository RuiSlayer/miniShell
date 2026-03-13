/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slayer <slayer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 17:23:13 by rucosta           #+#    #+#             */
/*   Updated: 2026/02/26 18:26:48 by slayer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	unsigned char	*ptr_big;
	unsigned char	*ptr_little;
	size_t			i;
	size_t			j;

	i = 0;
	ptr_big = (unsigned char *)big;
	ptr_little = (unsigned char *)little;
	if (ptr_little[0] == '\0')
		return ((char *)big);
	while (i < len && ptr_big[i] != '\0')
	{
		j = 0;
		while (ptr_little[j] != '\0' && (i + j) < len)
		{
			if (ptr_big[i + j] != ptr_little[j])
				break ;
			j++;
		}
		if (ptr_little[j] == '\0')
			return ((char *)ptr_big + i);
		i++;
	}
	return (NULL);
}
