/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slayer <slayer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 17:46:41 by slayer            #+#    #+#             */
/*   Updated: 2026/04/17 20:46:26 by slayer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/miniShell_exec.h"

int	built_export(t_cmd *cmds, t_env **env)
{
	int	i;
	int	status;

	if (!cmds->args[1])
		return (print_export(env));
	status = 0;
	i = 1;
	while (cmds->args[i] != NULL)
	{
		if (parse_var_name(cmds->args[i]))
		{
			ft_dprintf(2, "export: `%s': not a valid identifier\n",
				cmds->args[i]);
			i++;
			status = 1;
			continue ;
		}
		add_var(cmds->args[i], env);
		i++;
	}
	return (status);
}
