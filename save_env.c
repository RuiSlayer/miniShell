/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rucosta <rucosta@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 20:08:45 by rucosta           #+#    #+#             */
/*   Updated: 2026/02/24 23:02:52 by rucosta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniShell_exec.h"

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

void	find_var_val(t_env *node, char *envp)
{
	int	i;

	i = 0;
	while (envp[i] && envp[i] != '=')
		i++;
	node->var = ft_substr(envp, 0, i);
	if (envp[i] == '=')
		node->val = ft_strdup(envp + i + 1);
	else
		node->val = ft_strdup("");
}

void	save_node(t_env **env, char *envp, int i)
{
	t_env	*node;
	t_env	*temp;

	node = malloc(sizeof(t_env));
	if (!node)
		return ;
	node->next = NULL;
	find_var_val(node, envp);
	node->idx = i;
	if (*env == NULL)
		*env = node;
	else
	{
		temp = ms_lstlast(*env);
		temp->next = node;
	}
}

void	save_env(t_env **env, char **envp)
{
	int	i;

	*env = NULL;
	i = 0;
	while (envp[i] != NULL)
	{
		save_node(env, envp[i], i);
		i++;
	}
}

/* int main(int argc, char **argv, char **envp)
{
    t_env *env = NULL;
    t_env *tmp;

    save_env(&env, envp);

    tmp = env;
    while (tmp && tmp->idx != 5)
        tmp = tmp->next;
    if (tmp)
        printf("%s\n", tmp->val);

    return 0;
} */