/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds_runer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rucosta <rucosta@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/01 21:44:59 by rucosta           #+#    #+#             */
/*   Updated: 2026/04/07 03:52:00 by rucosta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/miniShell_exec.h"
#include <sys/stat.h>

void	external_cmds(t_shell *shell)
{
	char	**envp;
	char	*path;

	if (ft_strncmp(shell->cmds->args[0], "..", 3) == 0 || ft_strncmp(shell->cmds->args[0], ".", 2) == 0
		|| !**shell->cmds->args)
	{
		ft_dprintf(2, "%s: command not found\n", shell->cmds->args[0]);
		return (update_exit_status(shell, 127), clean_exit(shell));
	}
	path = ft_find_path(shell->cmds->args[0], shell->env);
	parse_external_cmd_path(shell, path);
	envp = env_to_array(shell->env);
	execve(path, shell->cmds->args, envp);
	ft_free_double_pointer(envp);
	if (errno == EACCES)
	{
		ft_dprintf(2, "%s: Permission denied\n", shell->cmds->args[0]);
		return (external_cmd_exit(shell, path, 1));
	}
	ft_dprintf(2, "%s: Unexpected execution error\n", shell->cmds->args[0]);
	external_cmd_exit(shell, path, 126);
}

void	run_builtin(t_shell *shell)
{
	if (ft_strcmp(shell->cmds->args[0], "exit") == 0)
		exit_built_in(shell);
	else if (ft_strcmp(shell->cmds->args[0], "echo") == 0)
		update_exit_status(shell, echo(shell->cmds));
	else if (ft_strcmp(shell->cmds->args[0], "pwd") == 0)
		update_exit_status(shell, pwd());
	else if (ft_strcmp(shell->cmds->args[0], "env") == 0)
		update_exit_status(shell, print_env(shell->env));
	else if (ft_strcmp(shell->cmds->args[0], "export") == 0)
		update_exit_status(shell, built_export(shell->cmds, &shell->env));
	else if (ft_strcmp(shell->cmds->args[0], "cd") == 0)
		update_exit_status(shell, cd(shell->cmds, &shell->env));
	else if (ft_strcmp(shell->cmds->args[0], "unset") == 0)
		update_exit_status(shell, unset(shell->cmds, &shell->env));
}

int	is_builtin(t_shell *shell)
{
	if (ft_strcmp(shell->cmds->args[0], "exit") == 0)
		return (1);
	else if (ft_strcmp(shell->cmds->args[0], "echo") == 0)
		return (1);
	else if (ft_strcmp(shell->cmds->args[0], "pwd") == 0)
		return (1);
	else if (ft_strcmp(shell->cmds->args[0], "env") == 0)
		return (1);
	else if (ft_strcmp(shell->cmds->args[0], "export") == 0)
		return (1);
	else if (ft_strcmp(shell->cmds->args[0], "cd") == 0)
		return (1);
	else if (ft_strcmp(shell->cmds->args[0], "unset") == 0)
		return (1);
	return (0);
}

void	run_builtin_in_parent(t_pipe *pipe_s, t_shell *shell)
{
	int	saved_in;
	int	saved_out;

	free(pipe_s);
	saved_in  = dup(STDIN_FILENO);
	saved_out = dup(STDOUT_FILENO);
	// Aplica redirects temporariamente no pai
	if (apply_redirects(shell->cmds->redirs) == -1)
	{
		dup2(saved_in,  STDIN_FILENO);
		dup2(saved_out, STDOUT_FILENO);
		close(saved_in); close(saved_out);
		return ;
	}
	run_builtin(shell);
	// Restaura stdin/stdout originais
	dup2(saved_in,  STDIN_FILENO);
	dup2(saved_out, STDOUT_FILENO);
	close(saved_in);
	close(saved_out);
}
