/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slayer <slayer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 17:46:41 by slayer            #+#    #+#             */
/*   Updated: 2026/03/14 17:41:53 by slayer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/miniShell_exec.h"

#include <stdlib.h>

t_env	**env_copy(int n, t_env *tmp)
{
	int		i;
	t_env	**arr;

	arr = malloc(sizeof(t_env *) * n);
	if (!arr)
		return (NULL);
	i = 0;
	while (tmp)
	{
		arr[i++] = tmp;
		tmp = tmp->next;
	}
	return (arr);
}

static int	env_size(t_env *env)
{
	int	n;

	n = 0;
	while (env)
	{
		n++;
		env = env->next;
	}
	return (n);
}

static void	sort_env_array(t_env **arr, int n)
{
	int		i;
	int		j;
	t_env	*tmp;

	i = 0;
	while (i < n - 1)
	{
		j = 0;
		while (j < n - 1 - i)
		{
			if (ft_strcmp(arr[j]->var, arr[j + 1]->var) > 0)
			{
				tmp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = tmp;
			}
			j++;
		}
		i++;
	}
}

int	print_export(t_env **env)
{
	t_env	*tmp;
	t_env	**arr;
	int		n;
	int		i;

	n = env_size(*env);
	tmp = *env;
	arr = env_copy(n, tmp);
	if (!arr)
		return (1);
	sort_env_array(arr, n);
	i = 0;
	while (i < n)
	{
		if (arr[i]->val)
			printf("declare -x %s=\"%s\"\n", arr[i]->var, arr[i]->val);
		else
			printf("declare -x %s\n", arr[i]->var);
		i++;
	}
	free(arr);
	return (0);
}

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

int	built_export(t_cmd *cmds, t_env **env)
{
	int	i;
	int	status;
	if(!cmds->args[1])
		return (print_export(env));
	status = 0;
	i = 1;
	while (cmds->args[i] != NULL)
	{
		if (parse_var_name(cmds->args[i]))
		{
			printf("export: %s: not a valid identifier\n", cmds->args[i]);
			i++;
			status = 1;
			continue ;
		}
		add_var(cmds->args[i], env);
		i++;
	}
	return (status);
}
