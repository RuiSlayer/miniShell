/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slayer <slayer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/02 20:19:27 by rucosta           #+#    #+#             */
/*   Updated: 2026/04/03 16:03:06 by slayer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/miniShell_exec.h"

void	update_exit_status(t_shell *shell, int status)
{
	shell->exit_status = status;
}

void	exit_built_in(t_shell *shell)
{
	int	arg;

	if (!shell->cmds->args[1])
		clean_exit(shell);
	if (shell->cmds->args[2])
	{
		printf("exit\nminiShell: exit: too many arguments\n");
		return ;
	}
	arg = ft_atoi(shell->cmds->args[1]);
	if (ft_isdigit(arg))
	{
		printf("exit\nminiShell: exit: %s: numeric argument required\n", shell->cmds->args[1]);
		return ;
	}
	update_exit_status(shell, arg);
	printf("exit\n");
	clean_exit(shell);
}

void	clean_exit(t_shell *shell)
{
	free_env(shell->env);
	ft_free_cmd_list(&shell->cmds);
	exit(shell->exit_status);
}
