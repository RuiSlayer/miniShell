/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slayer <slayer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/02 20:19:27 by rucosta           #+#    #+#             */
/*   Updated: 2026/04/11 18:20:34 by slayer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/miniShell_exec.h"

int	ft_is_numeric(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

void	update_exit_status(t_shell *shell, int status)
{
	shell->exit_status = status;
}

void	exit_built_in(t_shell *shell)
{
	int	arg;

	if (!shell->cmds->args[1])
		clean_exit(shell);
	if (!ft_is_numeric(shell->cmds->args[1]))
	{
		ft_dprintf(2, "miniShell: exit: %s: numeric argument required\n",
			shell->cmds->args[1]);
		update_exit_status(shell, 2);
		return ;
	}
	arg = ft_atoi(shell->cmds->args[1]);
	if (shell->cmds->args[2])
	{
		ft_dprintf(2, "miniShell: exit: too many arguments\n");
		update_exit_status(shell, 2);
		return ;
	}
	update_exit_status(shell, arg);
	clean_exit(shell);
}

void	clean_exit(t_shell *shell)
{
	if (shell->saved_in != -1)
		close(shell->saved_in);
	if (shell->saved_out != -1)
		close(shell->saved_out);
	free_env(shell->env);
	ft_free_cmd_list(&shell->cmds_head);
	if (!shell->is_subshell)
		ft_dprintf(2, RED"exit\n"RST);
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	exit(shell->exit_status);
}
