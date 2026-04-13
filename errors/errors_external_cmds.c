/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_external_cmds.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slayer <slayer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/07 03:26:41 by rucosta           #+#    #+#             */
/*   Updated: 2026/04/13 18:30:59 by slayer           ###   ########.fr       */
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

static void	print_error(t_shell *shell, char *path, char *message, int status)
{
	ft_dprintf(2, "test\n");
	ft_dprintf(2, "%s: %s\n", shell->cmds->args[0], message);
	return (external_cmd_exit(shell, path, status));
}

void	parse_external_cmd_execve(t_shell *shell, char *path, int error)
{
	if (error == EACCES)
		return (print_error(shell, path, "Permission denied", 126));
	if (error == ENOEXEC)
		return (print_error(shell, path, "Exec format error", 126));
	if (error == ENOENT)
		return (print_error(shell, path, "No such file or directory", 127));
	return (print_error(shell, path, "execve failed", 126));
}

void	parse_external_cmd_path(t_shell *shell, char *path)
{
	if (!path || access(path, F_OK) != 0)
	{
		if (errno == ENOTDIR)
			return (print_error(shell, path, "Not a directory", 126));
		if (ft_strchr(shell->cmds->args[0], '/')
			|| ft_strncmp(shell->cmds->args[0], "./", 2) == 0)
			return (print_error(shell, path, "No such file or directory", 127));
		return (print_error(shell, path, "command not found", 127));
	}
	if (is_directory(path) == 1)
		return (print_error(shell, path, "Is a directory", 126));
	if (access(path, X_OK) != 0)
		return (print_error(shell, path, "Permission denied", 126));
}
