/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rucosta <rucosta@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 21:28:55 by slayer            #+#    #+#             */
/*   Updated: 2026/02/18 17:14:16 by rucosta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniShell.h"

int	pwd(t_env *env)
{
	t_env *tmp;

	tmp = env;
	while (tmp)
	{
		if (tmp->var && ft_strncmp(tmp->var, "PWD", 3) == 0 && tmp->val)
			return (printf("%s\n", tmp->val), 0);
		tmp = tmp->next;
	}
	return (0);
}
