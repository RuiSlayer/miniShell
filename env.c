/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rucosta <rucosta@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 17:40:59 by rucosta           #+#    #+#             */
/*   Updated: 2026/02/24 23:02:59 by rucosta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniShell_exec.h"

int	print_env(t_env *env)
{
	t_env *tmp;

	tmp = env;
	while (tmp)
	{
		if (tmp->val && tmp->val[0] != '\0')
			printf("%s=%s\n", tmp->var, tmp->val);
		else if (tmp->val && tmp->val[0] == '\0')
			printf("%s=\n", tmp->var);
		/* if you want to completely skip variables without value, 
			remove the `else if` and keep only the first `if` */
		tmp = tmp->next;
	}
	return (0);
}
