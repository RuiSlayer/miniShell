/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgameiro <fgameiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 19:52:39 by fgameiro          #+#    #+#             */
/*   Updated: 2026/03/24 21:58:28 by fgameiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/expansion.h"

void	ft_append_char(char **result, char c)
{
	char	*tmp;
	char	buf[2];

	buf[0] = c;
	buf[1] = '\0';
	tmp = ft_strjoin(*result, buf);
	free(*result);
	*result = tmp;
}

void	ft_append_str(char **result, char *str)
{
	char	*tmp;

	if (!str)
		return;
	tmp = ft_strjoin(*result, str);
	free(*result);
	*result = tmp;
}

