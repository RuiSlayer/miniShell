/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slayer <slayer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/23 15:05:35 by fgameiro          #+#    #+#             */
/*   Updated: 2026/04/07 23:32:12 by slayer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/env.h"

char	*ft_getenv(t_env *env, char *name)
{
	while (env)
	{
		if (ft_strcmp(env->var, name) == 0)
			return (env->val);
		env = env->next;
	}
	return (NULL);
}

char	**env_to_array(t_env *env)
{
	t_env	*curr;
	char	**array;
	char	*tmp;
	int		count;
	int		i;

	count = 0;
	curr = env;
	while (curr)
		(count++, curr = curr->next);
	array = malloc(sizeof(char *) * (count + 1));
	if (!array)
		return (NULL);
	curr = env;
	i = 0;
	while (curr)
	{
		tmp = ft_strjoin(curr->var, "=");
		array[i] = ft_strjoin(tmp, curr->val);
		free(tmp);
		curr = curr->next;
		i++;
	}
	array[i] = NULL;
	return (array);
}
