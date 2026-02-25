/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slayer <slayer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 00:21:58 by rucosta           #+#    #+#             */
/*   Updated: 2026/02/25 16:46:34 by slayer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "42libft/libft.h"
#include "miniShell_exec.h"

void	free_var_val(char **var_val)
{
	int	i;

	i = 0;
	while (var_val[i])
		free(var_val[i++]);
	free(var_val);
}

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

void	add_var(char *arg, t_env *env)
{
	t_env *tmp;
	char	**var_val;

	tmp = env;
	var_val = ft_split(arg, '=');
	while (tmp)
	{
		 if (ft_strncmp(tmp->var, var_val[0], ft_strlen(var_val[0])) == 0)
		 {
			free(tmp->val);
			tmp->val = ft_strdup(var_val[1]);
			free_var_val(var_val);
			return;
		 }
		tmp = tmp->next;
	}
	create_node(var_val, env);
	free_var_val(var_val);
}

void	remove_var(char *arg, t_env *env)
{
	t_env	*tmp;
	t_env	*prev;

	tmp = env;
	prev = NULL;
	while (tmp)
	{
		if (ft_strncmp(tmp->var, arg, ft_strlen(arg)) == 0)
		{
			if (prev == NULL)
				env = tmp->next;
			else
				prev->next = tmp->next;
			free(tmp->val);
			free(tmp->var);
			free(tmp);
			return;
		}
		prev = tmp;
		tmp = tmp->next;
	}
}
