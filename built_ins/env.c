/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slayer <slayer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 17:40:59 by rucosta           #+#    #+#             */
/*   Updated: 2026/03/14 17:28:51 by slayer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/miniShell_exec.h"

int	print_env(t_env *env)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		if (tmp->val && tmp->val[0] != '\0')
			printf("%s=%s\n", tmp->var, tmp->val);
		else if (tmp->val && tmp->val[0] == '\0')
			printf("%s=\n", tmp->var);
		tmp = tmp->next;
	}
	return (0);
}
