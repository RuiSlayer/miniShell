/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slayer <slayer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 19:52:39 by fgameiro          #+#    #+#             */
/*   Updated: 2026/04/08 02:26:17 by slayer           ###   ########.fr       */
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
		return ;
	tmp = ft_strjoin(*result, str);
	free(*result);
	*result = tmp;
}
