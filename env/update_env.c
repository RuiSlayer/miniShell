/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgameiro <fgameiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 00:21:58 by rucosta           #+#    #+#             */
/*   Updated: 2026/03/28 19:12:42 by fgameiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/miniShell_exec.h"


static void	free_var_val(char **var_val)
{
	int	i;

	i = 0;
	while (var_val[i])
		free(var_val[i++]);
	free(var_val);
}

static void	create_node(char	**var_val, t_env **env)
{
	t_env	*new;
	t_env	*tmp;

	new = malloc(sizeof(t_env));
	if (!new)
		return ;
	new->var = ft_strdup(var_val[0]);
	if (var_val[1])
		new->val = ft_strdup(var_val[1]);
	else
		new->val = ft_strdup("");
	new->next = NULL;
	new->idx = 0;
	if (!env)
	{
		*env = new;
		return ;
	}
	tmp = *env;
	while (tmp->next)
		tmp = tmp->next;
	new->idx = tmp->idx + 1;
	tmp->next = new;
}

void	add_var(char *arg, t_env **env)
{
	t_env	*tmp;
	char	**var_val;

	tmp = *env;
	var_val = ft_split(arg, '=');
	while (tmp)
	{
		if (ft_strcmp(tmp->var, var_val[0]) == 0)
		{
			free(tmp->val);
			tmp->val = ft_strdup(var_val[1]);
			free_var_val(var_val);
			return ;
		}
		tmp = tmp->next;
	}
	create_node(var_val, env);
	free_var_val(var_val);
}

void	remove_var(char *arg, t_env **env)
{
	t_env	*tmp;
	t_env	*prev;

	tmp = *env;
	prev = NULL;
	while (tmp)
	{
		if (ft_strcmp(tmp->var, arg) == 0)
		{
			if (prev == NULL)
				*env = tmp->next;
			else
				prev->next = tmp->next;
			free(tmp->val);
			free(tmp->var);
			free(tmp);
			return ;
		}
		prev = tmp;
		tmp = tmp->next;
	}
}
