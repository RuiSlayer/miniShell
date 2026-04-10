/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_external_cmds.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slayer <slayer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/07 03:26:41 by rucosta           #+#    #+#             */
/*   Updated: 2026/04/11 00:30:37 by slayer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/miniShell_exec.h"

void	external_cmd_exit(t_shell *shell, char *path, int status)
{
	update_exit_status(shell, status);
	free(path);
	clean_exit(shell);
}

int	is_directory(const char *path)
{
	struct stat	st;

	if (stat(path, &st) != 0)
		return (-1);
	return (S_ISDIR(st.st_mode));
}

void	parse_external_cmd_execve(t_shell *shell, char *path, int error)
{
	if (error == EACCES)
	{
		ft_dprintf(2, "%s: Permission denied\n", shell->cmds->args[0]);
		external_cmd_exit(shell, path, 126);
	}
	else if (error == ENOEXEC)
	{
		ft_dprintf(2, "%s: Exec format error\n", shell->cmds->args[0]);
		external_cmd_exit(shell, path, 126);
	}
	else if (error == ENOENT)
	{
		ft_dprintf(2, "%s: No such file or directory\n", shell->cmds->args[0]);
		external_cmd_exit(shell, path, 127);
	}
	else
	{
		ft_dprintf(2, "%s: execve failed\n", shell->cmds->args[0]);
		external_cmd_exit(shell, path, 126);
	}
}

void	parse_external_cmd_path(t_shell *shell, char *path)
{
	if (!path || access(path, F_OK) != 0)
	{
		if (errno == ENOTDIR)
		{
			ft_dprintf(2, "%s: Not a directory\n", shell->cmds->args[0]);
			return (external_cmd_exit(shell, path, 126));
		}
		if (ft_strchr(shell->cmds->args[0], '/')
			|| ft_strncmp(shell->cmds->args[0], "./", 2) == 0)
		{
			ft_dprintf(2, "%s: No such file or directory\n",
				shell->cmds->args[0]);
			return (external_cmd_exit(shell, path, 127));
		}
		ft_dprintf(2, "minishell: %s: command not found\n",
			shell->cmds->args[0]);
		return (update_exit_status(shell, 127), clean_exit(shell));
	}
	if (is_directory(path) == 1)
	{
		ft_dprintf(2, "%s: Is a directory\n", shell->cmds->args[0]);
		return (external_cmd_exit(shell, path, 126));
	}
	if (access(path, X_OK) != 0)
	{
		ft_dprintf(2, "%s: Permission denied\n", shell->cmds->args[0]);
		return (external_cmd_exit(shell, path, 126));
	}
}
