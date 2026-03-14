/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slayer <slayer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 16:30:06 by slayer            #+#    #+#             */
/*   Updated: 2026/03/14 17:43:20 by slayer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/miniShell_exec.h"

int	unset(t_cmd *cmds, t_env **env)
{
	int	i;

	i = 1;
	while (cmds->args[i])
	{
		remove_var(cmds->args[i], env);
		i++;
	}
	return (0);
}
