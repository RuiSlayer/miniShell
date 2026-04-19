/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgameiro <fgameiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/18 23:56:26 by fgameiro          #+#    #+#             */
/*   Updated: 2026/04/19 00:02:52 by fgameiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/env.h"

static void	update_existing(t_env *tmp, char **var_val, int var_has_equal)
{
	if (!var_val[1] && !var_has_equal)
		return ;
	free(tmp->val);
	if (var_val[1])
		tmp->val = ft_strdup(var_val[1]);
	else if (var_has_equal)
		tmp->val = ft_strdup("");
}

static t_env	*find_var(char **var_val, t_env *tmp)
{
	while (tmp)
	{
		if (ft_strcmp(tmp->var, var_val[0]) == 0)
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}

void	add_var(char *arg, t_env **env)
{
	t_env	*tmp;
	t_env	*found;
	char	**var_val;
	int		var_has_equal;

	tmp = *env;
	var_has_equal = ft_is_char_in(arg, '=');
	var_val = ft_split_var(arg);
	found = find_var(var_val, tmp);
	if (found)
	{
		update_existing(found, var_val, var_has_equal);
		free_var_val(var_val);
		return ;
	}
	create_node(var_val, env, var_has_equal);
	free_var_val(var_val);
}
