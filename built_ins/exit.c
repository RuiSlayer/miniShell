/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slayer <slayer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/02 20:19:27 by rucosta           #+#    #+#             */
/*   Updated: 2026/04/17 20:22:54 by slayer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/miniShell_exec.h"

int	ft_is_numeric(char *str)
{
	int	i;

	i = 0;
	while (ft_isspace(str[i]))
		i++;
	if (str[i] == '+' || str[i] == '-')
		i++;
	if (!ft_isdigit(str[i]))
		return (0);
	while (ft_isdigit(str[i]))
		i++;
	while (ft_isspace(str[i]))
		i++;
	if (str[i])
		return (0);
	return (1);
}

void	update_exit_status(t_shell *shell, int status)
{
	shell->exit_status = status;
}

void	exit_built_in(t_shell *shell)
{
	int		arg;
	long	val;

	if (!shell->cmds->args[1])
		clean_exit(shell);
	val = ft_atol(shell->cmds->args[1]);
	if (!ft_is_numeric(shell->cmds->args[1]) || val > INT_MAX || val < INT_MIN)
	{
		ft_dprintf(2, "miniShell: exit: %s: numeric argument required\n",
			shell->cmds->args[1]);
		update_exit_status(shell, 2);
		clean_exit(shell);
	}
	arg = ft_atoi(shell->cmds->args[1]);
	if (shell->cmds->args[2])
	{
		ft_dprintf(2, "miniShell: exit: too many arguments\n");
		if (!shell->is_subshell)
			ft_dprintf(2, RED"exit\n"RST);
		update_exit_status(shell, 2);
		return ;
	}
	update_exit_status(shell, arg);
	clean_exit(shell);
}

void	clean_exit(t_shell *shell)
{
	close_fd(&shell->saved_in);
	close_fd(&shell->saved_out);
	free_env(shell->env);
	ft_free_cmd_list(&shell->cmds_head);
	if (!shell->is_subshell)
		ft_dprintf(2, RED"exit\n"RST);
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	close(STDERR_FILENO);
	exit(shell->exit_status);
}
