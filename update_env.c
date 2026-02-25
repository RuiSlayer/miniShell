/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rucosta <rucosta@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 00:21:58 by rucosta           #+#    #+#             */
/*   Updated: 2026/02/25 02:04:57 by rucosta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniShell_exec.h"

void	create_node(char	**var_val, t_env *env)
{
	t_env *new = malloc(sizeof(t_env));
	t_env *tmp;

	new->var = ft_strdup(var_val[0]);
	new->val = ft_strdup(var_val[1]);
	new->next = NULL;

	tmp = env;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

void	add_var(char *line, t_env *env)
{
	int	i;
	t_env *tmp;
	char	**var_val;

	i = 0;
	tmp = env;
	var_val = ft_split(line, '=');
	while (tmp)
	{
		 if (strcmp(tmp->var, var_val[0]) == 0)
		 {
			free(tmp->val);
			tmp->val = ft_strdup(var_val[1]);
			while (var_val[i])
				free(var_val[i++]);
			free(var_val);
			return;
		 }
		tmp = tmp->next;
	}
	create_node(var_val, env);
	while (var_val[i])
		free(var_val[i++]);
	free(var_val);
}

