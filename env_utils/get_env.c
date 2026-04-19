/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgameiro <fgameiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/23 15:05:35 by fgameiro          #+#    #+#             */
/*   Updated: 2026/04/18 21:51:31 by fgameiro         ###   ########.fr       */
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

static int	ft_env_count(t_env *env)
{
	int	i;

	i = 0;
	while (env)
	{
		i++;
		env = env->next;
	}
	return (i);
}

char	**env_to_array(t_env *env)
{
	char	**array;
	char	*tmp;
	int		i;

	array = malloc(sizeof(char *) * (ft_env_count(env) + 1));
	if (!array)
		return (NULL);
	i = 0;
	while (env)
	{
		tmp = ft_strjoin(env->var, "=");
		array[i] = ft_strjoin(tmp, env->val);
		free(tmp);
		env = env->next;
		i++;
	}
	array[i] = NULL;
	return (array);
}

int	ft_is_char_in(const char *s, int c)
{
	while (*s)
	{
		if ((char)c == *s)
			return (1);
		s++;
	}
	if ((char)c == '\0')
		return (0);
	return (0);
}
