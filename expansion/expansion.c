/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgameiro <fgameiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 19:52:42 by fgameiro          #+#    #+#             */
/*   Updated: 2026/03/23 16:23:27 by fgameiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/expansion.h"

void	ft_handle_expansion(char *str, size_t *i, char **result, char **envp, int exit_status)
{
	char	*var_name;
	char	*value;

	var_name = ft_get_var_name(str, i);
	if (!var_name)
		return ;
	if (ft_strcmp(var_name, "?") == 0)
		value = ft_itoa(exit_status);
	else
		value = getenv(var_name);
	if (value)
		ft_append_str(result, value);
	free(var_name);
}
