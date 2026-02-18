/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rucosta <rucosta@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 17:46:41 by slayer            #+#    #+#             */
/*   Updated: 2026/02/18 20:08:33 by rucosta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniShell.h"

char	**get_val(char *line)
{
	int	i;
	int	beguin;
	int	j;
	char	**vals;

	i = 5;
	while(line[i] != '=')
		i++;
	beguin = i + 2;
	while (line[i] != '\0')
	{
		if (line[i] == ' ')
		{
			vals[j] = ft_substr(line, beguin, i - 1);
			j++;
			while((line[i] != '\0') && (line[i] != '='))
				i++;
			beguin = i;
		}
		i++;
	}
	return (vals);
}

char	**get_var(char *line)
{
	int	i;
	int	beguin;
	int	j;
	char	**vars;

	i = 5;
	while(line[i] == ' ')
		i++;
	beguin = i;
	while (line[i] != '\0')
	{
		if (line[i] == '=')
		{
			vars[j] = ft_substr(line, beguin, i - 1);
			j++;
			while((line[i] != '\0') && (line[i] != ' '))
				i++;
			beguin = i;
		}
		i++;
	}
	return (vars);
}

int	export(char *line, t_env *env)
{
	t_env *tmp;
	int	i;
	char	**vars;
	char	**vals;

	vars = get_var(line);
	vals = get_vals(line);
	tmp = env;
	i = 0;
	while (tmp)
	{
		if (ft_strncmp(tmp->var, vars[i], ft_strlen(vars[i])) == 0)
		{
			tmp->val = vals[i];
			i++;
		}
		tmp = tmp->next;
	}
	return (0);
}
