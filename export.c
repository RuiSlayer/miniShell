/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slayer <slayer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 17:46:41 by slayer            #+#    #+#             */
/*   Updated: 2026/02/26 17:25:40 by slayer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniShell_exec.h"

int	parse_var_name(char *arg)
{
	int	i;

	if (!arg || !arg[0])
		return (1);
	i = 0;
	if (!(ft_isalpha(arg[i])) && (arg[i] != '_'))
		return (1);
	i++;
	while (arg[i] && arg[i] != '=')
	{
		if (!(ft_isalnum(arg[i])) && (arg[i] != '_'))
			return (1);
		i++;
	}
	return (0);
}

int	export(char **args, t_env *env)
{
	int	i;
	int	status;

	status = 0;
	i = 0;
	while (args[i])
	{
		if (parse_var_name(args[i]))
		{
			printf("export: %s: not a valid identifier\n", args[i]);
			i++;
			status = 1;
			continue ;
		}
		add_var(args[i], env);
		i++;
	}
	return (status);
}
