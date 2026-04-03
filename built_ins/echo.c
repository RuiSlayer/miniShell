/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rucosta <rucosta@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 15:36:17 by slayer            #+#    #+#             */
/*   Updated: 2026/04/02 22:45:06 by rucosta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/miniShell_exec.h"

static int	echo_n(char **args, int *newline)
{
	int	i;
	int	j;

	*newline = 1;
	i = 1;
	while (args[i])
	{
		if (strncmp(args[i], "-n", 2) == 0)
		{
			j = 1;
			while (args[i][j] == 'n')
				j++;
			if (args[i][j] == '\0')
			{
				*newline = 0;
				i++;
			}
			else
				break ;
		}
		else
			break ;
	}
	return (i);
}

int	echo(t_cmd	*cmd)
{
	int	i;
	int	newline;

	i = echo_n(cmd->args, &newline);
	while (cmd->args[i])
	{
		ft_putstr_fd(cmd->args[i], STDOUT_FILENO);
		if (cmd->args[i + 1])
			ft_putstr_fd(" ", STDOUT_FILENO);
		i++;
	}
	if (newline)
		ft_putstr_fd("\n", STDOUT_FILENO);
	return (0);
}
