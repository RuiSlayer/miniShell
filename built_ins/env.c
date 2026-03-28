/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rucosta <rucosta@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 17:40:59 by rucosta           #+#    #+#             */
/*   Updated: 2026/03/28 21:18:03 by rucosta          ###   ########.fr       */
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
		tmp = tmp->next;
	}
	return (0);
}
