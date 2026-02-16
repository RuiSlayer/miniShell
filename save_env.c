/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rucosta <rucosta@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 20:08:45 by rucosta           #+#    #+#             */
/*   Updated: 2026/02/16 20:38:30 by rucosta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniShell.h"

t_env	*ms_lstlast(t_env *lst)
{
	t_env	*ls;

	ls = lst;
	if (ls != NULL)
	{
		while (ls->next != NULL)
			ls = ls->next;
	}
	return (ls);
}

int	truncate(t_env *node, char *envp)
{
	
}

int	save_node(t_env **env, char *envp, int	first)
{
	t_env	*node;
	t_env	*temp;

	node = malloc(sizeof(t_env));
	truncate(node, envp);
	if(first)
		(*env) = node;
	else
	{
		temp = s_lstlast(*env);
		temp->next = node;
	}
}

int	save_env(t_env **env, char **envp)
{
	int		i;
	int		size;

	i = 0;
	while(envp[i] != NULL)
	{
		if(env == NULL)
			save_node(env, envp[i], 1);
		else
			save_node(env, envp[i], 0);
	}
}
