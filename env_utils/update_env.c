/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgameiro <fgameiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 00:21:58 by rucosta           #+#    #+#             */
/*   Updated: 2026/04/19 00:00:14 by fgameiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/miniShell_exec.h"

void	free_var_val(char **var_val)
{
	int	i;

	i = 0;
	while (var_val[i])
		free(var_val[i++]);
	free(var_val);
}

void	create_node(char **var_val, t_env **env, int var_has_equal)
{
	t_env	*new;
	t_env	*tmp;

	new = malloc(sizeof(t_env));
	if (!new)
		return ;
	new->var = ft_strdup(var_val[0]);
	if (var_val[1])
		new->val = ft_strdup(var_val[1]);
	else if (var_has_equal)
		new->val = ft_strdup("");
	else
		new->val = NULL;
	new->next = NULL;
	new->idx = 0;
	if (!*env)
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

char	**ft_split_var(char *arg)
{
	char	**var_val;
	char	*equal;

	var_val = malloc(sizeof(char *) * 3);
	if (!var_val)
		return (NULL);
	equal = ft_strchr(arg, '=');
	if (equal)
	{
		var_val[0] = ft_substr(arg, 0, equal - arg);
		var_val[1] = ft_strdup(equal + 1);
	}
	else
	{
		var_val[0] = ft_strdup(arg);
		var_val[1] = NULL;
	}
	var_val[2] = NULL;
	return (var_val);
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
